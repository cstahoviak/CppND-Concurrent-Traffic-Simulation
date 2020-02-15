#include <algorithm>
#include <iostream>
#include <chrono>
#include "TrafficObject.h"

/* NOTE:
* "There will not be an instance of TrafficObject, but it will be used as a
* virtual class. The Intersection, Street and Vehicle  will each be a "child
* object" of TrafficObject."
*/

/* TASK L1.1:
* Setup a "thread barrier" in the class destructor that ensures that all the
* thread objects (Vehicles and ??) in the member vector _threads are joined.
*/  

// init static variable
int TrafficObject::_idCnt = 0;

std::mutex TrafficObject::_mtx;

void TrafficObject::setPosition(double x, double y)
{
    _posX = x;
    _posY = y;
}

void TrafficObject::getPosition(double &x, double &y)
{
    x = _posX;
    y = _posY;
}

TrafficObject::TrafficObject()
{
    _type = ObjectType::noObject;
    _id = _idCnt++;
}

TrafficObject::~TrafficObject()
{
    // TASK L1.1: set up thread barrier before this object is destroyed
    std::for_each(_threads.begin(), _threads.end(), [](std::thread &t) {
        t.join();
    });
}
