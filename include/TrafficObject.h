#ifndef TRAFFICOBJECT_H
#define TRAFFICOBJECT_H

#include <vector>
#include <thread>
#include <mutex>

enum ObjectType
{
    noObject,
    objectVehicle,
    objectIntersection,
    objectStreet,
};

class TrafficObject
{
public:
    // constructor / desctructor
    TrafficObject();
    ~TrafficObject();

    // getter and setter
    int getID() { return _id; }
    void setPosition(double x, double y);
    void getPosition(double &x, double &y);
    ObjectType getType() { return _type; }

    // typical behaviour methods
    // NOTE: the "virtual" modifier indicates that this method can (and should) be
    // overwritten by classes which are derived from the TrafficObject class, e.g.
    // the Vehicle, Intersection and Street classes will implement their own
    // simulate() method.
    virtual void simulate(){};

protected:
    ObjectType _type;                   // identifies the class type
    int _id;                            // every traffic object has its own unique id
    double _posX, _posY;                // vehicle position in pixels
    std::vector<std::thread> _threads;  // holds all threads that have been launched within this object
    static std::mutex _mtx;             // mutex shared by all traffic objects for protecting cout 

private:
    // NOTE: the "static" modifier indicates that this member variable is
    // independent of instances of TrafficObject
    // NOTE: Each time a TrafficObject )or and object of a class that has been derived
    // from a TrafficObject) is instantiated, this counter is incremented by one
    static int _idCnt; // global variable for counting object ids
};

#endif