/*
 * GPIO.h
 *
 *  Created on: Jan 25, 2018
 *      Author: maxime
 */

#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include <string>
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>


std::string toggle_value(std::string value);
int gpio_export(std::string PNXX, std::string direction);
int gpio_unexport(std::string PNXX);
int gpio_set_event(std::string PNXX, std::string event);
int gpio_set_value(std::string PNXX, std::string value);
int gpio_get_value(std::string PNXX, std::string &value);
int gpio_wait_for_event(std::string PNXX, std::string &value, short events, int timeout);




#endif /* INC_GPIO_H_ */
