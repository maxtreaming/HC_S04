/*
 * ProximitySensor.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: maxime
 */

#include "ProximitySensor.h"

ProximitySensor::ProximitySensor(std::string trigger, std::string echo, int count_to_mean) : run_process(true), count_to_mean(count_to_mean), pin_trigger(trigger), pin_echo(echo), mean_value(0), sum_value(0)
{
	gpio_export(pin_trigger, "low");
	gpio_export(pin_echo, "in");

	my_thread.reset (new std::thread(&ProximitySensor::process, this));
}

ProximitySensor::~ProximitySensor()
{
	my_thread->join();
	gpio_unexport(pin_trigger);
	gpio_unexport(pin_echo);
}

void ProximitySensor::process()
{
	int current_measure = 0;
	while(run_process)
	{
		send_initial_signial();
		measure();
		if(current_measure++ >= count_to_mean)
		{
			count_mean();
			current_measure = 0;
		}
	}
}

double ProximitySensor::get_distance()
{
	std::lock_guard<std::mutex> lock(mutex_measure);
	return mean_value;
}

void ProximitySensor::count_mean()
{
	mutex_measure.lock();
	mean_value = sum_value / count_to_mean;
	mutex_measure.unlock();
	sum_value = 0;
}

void ProximitySensor::send_initial_signial()
{
	gpio_set_value(pin_trigger, "1");
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	gpio_set_value(pin_trigger, "0");
}

void ProximitySensor::measure()
{
	std::string value = "0";
	gpio_get_value(pin_echo, value);
	auto start = std::chrono::system_clock::now();
	auto end = start;
	while(value == "0" && std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() < 60)
	{
		gpio_get_value(pin_echo, value);
		end = std::chrono::system_clock::now();
	}
	start = std::chrono::system_clock::now();
	end = start;
	while(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() < timeout && value == "1")
	{
		gpio_get_value(pin_echo, value);
		end = std::chrono::system_clock::now();
	}
	if(value == "0")
		sum_value += (double)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 58;
	else
		sum_value--;
}

void ProximitySensor::end_measure()
{
	run_process = false;
}

