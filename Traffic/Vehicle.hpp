#ifndef VEHICLE_HPP
#define VEHICLE_HPP

// This use of <queue> is allowed, but you should not use it in your own code.
#include <queue>

/*
The vehicle class represents a single vehicle travelling along a road. Each vehicle has a type, a number of occupants,
and a queue of turns it must make along its journey. If the vehicle's turn queue is empty, by default it will attempt to
keep going straight.

You should not modify this class.
*/
class Vehicle {
public:
    /*
    The Type enum descibes the type of vehicle this object represents, this can currently be either a car, bus or
    motorcycle.
    */
    enum Type {
        VT_CAR,
        VT_BUS,
        VT_MOTORCYCLE,

        VT_INVALID
    };

    /*
    The TurnDirection enum is used to indicate or set the direction that this vehicle wants to turn at the next
    intersection it reaches.
    */
    enum TurnDirection { TD_LEFT, TD_STRAIGHT, TD_RIGHT, TD_INVALID };

    /*
    The Vehicle constructor; sets the type of the vehicle (which cannot change) and the number of occupants in the
    vehicle. By default, the direction the car wants to turn in will be set to TD_STRAIGHT; to change it, call the
    appropriate methods of this class.
    */
    Vehicle(Type newType, unsigned int occupantCount);

    /*
    Get the type of this vehicle. Inspect the definition of the Type enum for more information about vehicle types.
    */
    Type type() const;

    /*
    Get the current number of occupants in the vehicle.
    */
    unsigned int occupantCount() const;

    /*
    Get the the direction of the next turn this Vehicle will make. The turn will not be removed from the turn queue. If
    there are no turns left to make this method will return TD_INVALID.
    */
    TurnDirection nextTurn() const;

    /*
    Get the direction of the next turn this Vehicle will make, removing it from the turn queue. If there are no turns
    left to make this method will return TD_INVALID.
    */
    TurnDirection makeTurn();

    /*
    Add a left turn (TD_RIGHT) to the turn queue, indicating this Vehicle will turn left at the corresponding
    intersection if possible.
    */
    void turnLeft();

    /*
    Add a right turn (TD_RIGHT) to the turn queue, indicating this Vehicle will turn right at the corresponding
    intersection if possible.
    */
    void turnRight();

    /*
    Add a straight turn (TD_STRAIGHT) to the turn queue, indicating this Vehicle will travel straight through the
    corresponding intersection if possible.
    */
    void turnStraight();

private:
    /*
    Private Vehicle copy constructor - vehicles cannot be copied, must be passed around via pointers and references.
    */
    Vehicle(const Vehicle&){};

    /*
    Private Vehicle copy assignment operator - vehicles cannot be copied, must be passed around via pointers and
    references.
    */
    Vehicle& operator=(const Vehicle&) {
        return *this;
    };

    Type vehicleType;
    unsigned int occupants;
    std::queue<TurnDirection> turns;
};

#endif /* end of include guard: VEHICLE_HPP */
