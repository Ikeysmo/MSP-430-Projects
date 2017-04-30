/*
 * hamburger.h
 *
 *  Created on: Jan 5, 2017
 *      Author: Isaiah
 */

#ifndef HAMBURGER_H_
#define HAMBURGER_H_
#include <msp430.h>

class hamburger
{
public:
    int ham;
    hamburger();
    void toggleLED();
    virtual ~hamburger();
};

#endif /* HAMBURGER_H_ */
