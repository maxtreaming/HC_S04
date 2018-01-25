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


std::string toggle_value(std::string value);
int gpio_export(std::string PNXX, std::string direction);
int gpio_unexport(std::string PNXX);
int gpio_set_value(std::string PNXX, std::string value);
int gpio_get_value(std::string PNXX, std::string &value);




#endif /* INC_GPIO_H_ */
