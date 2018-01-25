/*
 * main.cpp
 *
 *  Created on: Jan 25, 2018
 *      Author: maxime
 */

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <atomic>

#include "../ProximitySensor.h"


using namespace std;

void wait_key(bool* flag)
{
	string a = "";
	while(a != "q")
		std::cin >> a;

	*flag = false;
}

int main()
{

	ProximitySensor HC_SO4("PA12", "PA11", 3);
	bool run_program;
	run_program = true;

	std::thread key_wait(wait_key, &run_program);

	while(run_program)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		double value = HC_SO4.get_distance();
		if(value > 0)
			std::cout <<  value <<  "cm" << std::endl;
		else
			std::cout << "Distance out of range" << std::endl;
	}

	HC_SO4.end_measure();
	if(key_wait.joinable())
		key_wait.join();

	return 0;
}



