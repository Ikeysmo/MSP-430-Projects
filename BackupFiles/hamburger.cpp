/*
 * hamburger.cpp
 *
 *  Created on: Jan 5, 2017
 *      Author: Isaiah
 */

#include "hamburger.h"

hamburger::hamburger()
{
    PJDIR |= 0x02;
    ham= 0; // TODO Auto-generated constructor stub

}

hamburger::~hamburger()
{
    // TODO Auto-generated destructor stub
}

void hamburger::toggleLED(){
    PJOUT ^= 0x02;
}
