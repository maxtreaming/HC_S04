/*
 * ProximitySensor.h
 *
 *  Created on: Jan 25, 2018
 *      Author: maxime
 */

#ifndef PROXIMITYSENSOR_H_
#define PROXIMITYSENSOR_H_

#include <thread>
#include <mutex>
#include <chrono>
#include <memory>
#include <atomic>
#include "inc/GPIO.h"

const int ultra_sonic_pulse_timeout = 60;
const int timeout = 12; //milliseconds

class ProximitySensor {
private:
	std::unique_ptr<std::thread> my_thread;
	std::atomic<bool> run_process;
	int count_to_mean;
	double mean_value, sum_value;
	std::string pin_trigger, pin_echo;
	std::mutex mutex_measure;

	void process();
	void count_mean();
	void send_initial_signial();
	int measure();

public:
	ProximitySensor(std::string trigger, std::string echo, int count_to_mean = 10);
	double get_distance();
	void end_measure();
	virtual ~ProximitySensor();
};

#endif /* PROXIMITYSENSOR_H_ */
