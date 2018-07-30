#ifndef EXPRESSLANE_HPP
#define EXPRESSLANE_HPP

#include "SimpleLane.hpp"

/*
The ExpressLane class simulates a single lane of a road. It is a FIFO queue for Vehicle objects.

ExpressLane implements the same behavior as SimpleLane, except when a Vehicle of type VT_MOTORCYCLE is enqueued, that
Vehicle is inserted ahead of all Vehicles of type VT_CAR and VT_BUS, but behind other motorcycles that have already been
enqueued.
*/
class ExpressLane : public SimpleLane {
public:
	void enqueue(Vehicle* vehicle);
};

#endif /* end of include guard: EXPRESSLANE_HPP */
