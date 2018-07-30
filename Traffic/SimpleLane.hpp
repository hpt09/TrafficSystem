#ifndef SIMPLELANE_HPP
#define SIMPLELANE_HPP

#include "Lane.hpp"
#include "Node.h"

/*
The SimpleLane class simulates a single lane of a road. It is a FIFO queue for Vehicle objects.

Vehicles can be added to the back of the lane with the enqueue() method and removed from the front of the lane using the
dequeue() method.
*/
class SimpleLane : public Lane {
protected:
	Node *frontVehicle;
	Node *lastVehicle;
	int sum;
public:
	/*
	Create a new empty traffic lane. Remember to initialize member variables where necessary.
	*/
	SimpleLane();

	/*
	Destroy the lane; the destructor should delete *all* vehicles currently enqueued in the lane.
	*/
	virtual ~SimpleLane();

	/*
	Add a Vehicle to the back of the lane.
	*/
	virtual void enqueue(Vehicle* vehicle);

	/*
	Remove a vehicle from the front of the lane, returning a pointer to the removed vehicle. If there is no vehicle to
	remove, this method should return 0 instead.
	*/
	virtual Vehicle* dequeue();

	/*
	Return whether or not the lane is empty; the returned value is `true` if there are no vehicles in the lane, or
	`false` if there is at least one vehicle in the lane.
	*/
	virtual bool empty() const;

	/*
	Get the exact number of vehicles currently in the lane; e.g. should return 0 if there are no vehicles in the lane,
	or 4 if there are four vehicles in the lane.
	*/
	virtual unsigned int count() const;

	/*
	Return a pointer to the vehicle at the front of the lane without removing it from the lane. If there are no vehicles
	in the lane this method should return 0.
	*/
	virtual const Vehicle* front() const;

	/*
	Return a pointer to the vehicle at the back of the lane without removing it from the lane. If there are no vehicles
	in the lane this method should return 0.
	*/
	virtual const Vehicle* back() const;
};

#endif /* end of include guard: SIMPLELANE_HPP */
