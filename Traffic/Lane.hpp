#ifndef LANE_HPP
#define LANE_HPP

// forward declaration to save having to include the Vehicle header
class Vehicle;

/*
The Lane class simulates a single lane of a road. It is a FIFO queue for Vehicle objects.

Vehicles can be added to the end of the lane with the push() method and removed from the front of the lane using the
pop() method.
*/
class Lane {
public:
    /*
    Lane destructor declared as virtual so that the appropriate destructor is called on polymorphic Lane objects.
    */
    virtual ~Lane(){};

    /*
    Add a Vehicle to the back of the lane.
    */
    virtual void enqueue(Vehicle* vehicle) = 0;

    /*
    Remove a vehicle from the front of the lane, returning a pointer to the removed vehicle. If there is no vehicle to
    remove, this method should return 0 instead.
    */
    virtual Vehicle* dequeue() = 0;

    /*
    Return whether or not the lane is empty; the returned value is `true` if there are no vehicles in the lane, or
    `false` if there is at least one vehicle in the lane.
    */
    virtual bool empty() const = 0;

    /*
    Get the exact number of vehicles currently in the lane; e.g. should return 0 if there are no vehicles in the lane,
    or 4 if there are four vehicles in the lane.
    */
    virtual unsigned int count() const = 0;

    /*
    Return a pointer to the vehicle at the front of the lane without removing it from the lane. If there are no vehicles
    in the lane this method should return 0.
    */
    virtual const Vehicle* front() const = 0;

    /*
    Return a pointer to the vehicle at the back of the lane without removing it from the lane. If there are no vehicles
    in the lane this method should return 0.
    */
    virtual const Vehicle* back() const = 0;
};

#endif /* end of include guard: LANE_HPP */