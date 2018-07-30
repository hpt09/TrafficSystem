#include <iostream>
#include <cctype>
#include <cstdlib>
#include <vector>

// flags to enable tests for the later parts of the assignment
#define ENABLE_VEHICLE_TESTS
#define ENABLE_T1_TESTS
#define ENABLE_T2_TESTS

// include headers for classes being tested
#include "Traffic/Vehicle.hpp"
#ifdef ENABLE_T1_TESTS
#include "Traffic/Lane.hpp"
#include "Traffic/SimpleLane.hpp"
#include "Traffic/ExpressLane.hpp"
#endif /*ENABLE_T1_TESTS*/
#ifdef ENABLE_T2_TESTS
#include "Traffic/Lane.hpp"
#include "Traffic/SimpleLane.hpp"
#include "Traffic/ExpressLane.hpp"
#include "Traffic/Intersection.hpp"
#endif /*ENABLE_T2_TESTS*/

using namespace std;

// This sigma value is the acceptable range of error for floating point (double) calculations
const double SIGMA = 0.001;

/*
The outcome of each test case is described by this enum, which should make the result more obvious
than if a boolean value was used in its place.
*/
enum TestResult { TR_PASS, TR_FAIL };

/*
Helper macro to eliminate a lot of of code repetition. Macros aren't the best, but this is an easy
way to get what we want.
*/

#define ASSERT(condition)                                                         \
    if ((condition) == false) {                                                   \
        cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                \
             << "\tExpression '" << #condition << "' evaluated to false" << endl; \
        return TR_FAIL;                                                           \
    }

/*
Helper macro to simplify the checking of double values against expected results. Directly comparing
values would result in brittle tests, so we have to instead check if the value we got is acceptably
close to the expected value.
*/
#define EXPECT_SIGMA(value, expected)                                                                            \
    {                                                                                                            \
        double value_eval = value;                                                                               \
        double expected_eval = expected;                                                                         \
        if (value_eval <= (expected_eval - SIGMA) || value_eval > (expected_eval + SIGMA)) {                     \
            cout << "FAILURE: " << __FILE__ << ":" << __LINE__ << "\n"                                           \
                 << "\tFloating-point value " << value_eval << " differed from expected value " << expected_eval \
                 << " by more than " << SIGMA << endl;                                                           \
            return TR_FAIL;                                                                                      \
        }                                                                                                        \
    }

#ifdef ENABLE_VEHICLE_TESTS
/*
Test setting the vehicle type and number of occupants in the Vehicle constructor
*/
TestResult test_VehicleConstruction() {
    {
        Vehicle c(Vehicle::VT_CAR, 2);
        ASSERT(c.type() == Vehicle::VT_CAR);
        ASSERT(c.occupantCount() == 2);
    }

    {
        Vehicle b(Vehicle::VT_BUS, 14);
        ASSERT(b.type() == Vehicle::VT_BUS);
        ASSERT(b.occupantCount() == 14);
    }

    {
        Vehicle b(Vehicle::VT_MOTORCYCLE, 1);
        ASSERT(b.type() == Vehicle::VT_MOTORCYCLE);
        ASSERT(b.occupantCount() == 1);
    }

    return TR_PASS;
}

/*
Test the turn direction functionality of the Vehicle class.
*/
TestResult test_VehicleTurning() {
    Vehicle c(Vehicle::VT_CAR, 2);
    // Test car with empty turn queue
    ASSERT(c.nextTurn() == Vehicle::TD_INVALID);
    ASSERT(c.makeTurn() == Vehicle::TD_INVALID);

    // Queue some turns and go through them
    c.turnLeft();
    c.turnRight();
    c.turnStraight();

    ASSERT(c.nextTurn() == Vehicle::TD_LEFT);
    ASSERT(c.makeTurn() == Vehicle::TD_LEFT);
    ASSERT(c.nextTurn() == Vehicle::TD_RIGHT);
    ASSERT(c.makeTurn() == Vehicle::TD_RIGHT);
    ASSERT(c.nextTurn() == Vehicle::TD_STRAIGHT);
    ASSERT(c.makeTurn() == Vehicle::TD_STRAIGHT);

    // Test empty queue again, after turns executed
    ASSERT(c.nextTurn() == Vehicle::TD_INVALID);
    ASSERT(c.makeTurn() == Vehicle::TD_INVALID);

    return TR_PASS;
}
#endif /*ENABLE_VEHICLE_TESTS*/

#ifdef ENABLE_T1_TESTS
/*
Test Lane construction (and destruction).
*/
TestResult test_SimpleLaneConstruction() {
    // scope the instance to explicitly invoke the destructor before the return
    {
        SimpleLane lane;
        // prevent the compiler from optimizing out the instance
        (void)lane;
    }

    return TR_PASS;
}

/*
Test SimpleLane initial state.
*/
TestResult test_SimpleLaneInitialState() {
    SimpleLane lane;

    ASSERT(lane.front() == 0);
    ASSERT(lane.back() == 0);
    ASSERT(lane.dequeue() == 0);
    ASSERT(lane.empty() == true);
    ASSERT(lane.count() == 0);

    return TR_PASS;
}

/*
Test adding vehicles to the SimpleLane.
*/
TestResult test_SimpleLaneEnqueue() {
    SimpleLane lane;
    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    Vehicle* v2 = new Vehicle(Vehicle::VT_CAR, 2);
    Vehicle* v3 = new Vehicle(Vehicle::VT_BUS, 3);
    Vehicle* m1 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);

    lane.enqueue(v1);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 1)
    ASSERT(lane.back() == v1);
    ASSERT(lane.front() == v1);
    lane.enqueue(v2);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 2)
    ASSERT(lane.back() == v2);
    ASSERT(lane.front() == v1);
    lane.enqueue(v3);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 3)
    ASSERT(lane.back() == v3);
    ASSERT(lane.front() == v1);
    lane.enqueue(m1);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 4)
    ASSERT(lane.back() == m1);
    ASSERT(lane.front() == v1);

    // vehicles should be deleted by the lane
    return TR_PASS;
}

// modified by hamish
TestResult test_SimpleLaneEnqueueModified() {
    SimpleLane lane;
    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    Vehicle* v2 = new Vehicle(Vehicle::VT_CAR, 2);
    Vehicle* v3 = new Vehicle(Vehicle::VT_BUS, 3);
    Vehicle* m1 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);

    lane.enqueue(v1);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 1)
    ASSERT(lane.back() == v1);
    ASSERT(lane.front() == v1);
    lane.enqueue(v2);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 2)
    ASSERT(lane.back() == v2);
    ASSERT(lane.front() == v1);
    lane.enqueue(v3);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 3)
    ASSERT(lane.back() == v3);
    ASSERT(lane.front() == v1);
    lane.enqueue(m1);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 4)
    ASSERT(lane.back() == m1);
    ASSERT(lane.front() == v1);

    ASSERT(lane.dequeue() == v1);
	ASSERT(!lane.empty())
	ASSERT(lane.count() == 3)
	ASSERT(lane.back() == m1);
	ASSERT(lane.front() == v2);
	ASSERT(lane.dequeue() == v2);
	ASSERT(!lane.empty())
	ASSERT(lane.count() == 2)
	ASSERT(lane.back() == m1);
	ASSERT(lane.front() == v3);
	ASSERT(lane.dequeue() == v3);
	ASSERT(!lane.empty())
	ASSERT(lane.count() == 1)
	ASSERT(lane.back() == m1);
	ASSERT(lane.front() == m1);
	ASSERT(lane.dequeue() == m1);
	ASSERT(lane.empty())
	ASSERT(lane.count() == 0)
	ASSERT(lane.back() == 0);
	ASSERT(lane.front() == 0);

    // vehicles need to be deleted by us
	delete v1;
	delete v2;
	delete v3;
	delete m1;

    return TR_PASS;
}

// from piazza @418, modified by hamish
TestResult test_SimpleLaneDequeue() {
	SimpleLane lane;
	Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
	Vehicle* v2 = new Vehicle(Vehicle::VT_CAR, 2);
	Vehicle* v3 = new Vehicle(Vehicle::VT_BUS, 3);
	Vehicle* m1 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);
	lane.enqueue(v1);
	lane.enqueue(v2);
	lane.enqueue(v3);
	lane.enqueue(m1);
	ASSERT(lane.dequeue() == v1);
	ASSERT(lane.count() == 3)
	ASSERT(lane.front() == v2);
	ASSERT(lane.back() == m1);
	ASSERT(lane.dequeue() == v2);
	ASSERT(lane.count() == 2)
	ASSERT(lane.front() == v3);
	ASSERT(lane.back() == m1);
	ASSERT(lane.dequeue() == v3);
	ASSERT(lane.count() == 1)
	ASSERT(lane.front() == m1);
	ASSERT(lane.back() == m1);
	ASSERT(lane.dequeue() == m1);
	ASSERT(lane.count() == 0)
	ASSERT(lane.front() == 0);
	ASSERT(lane.back() == 0);
	ASSERT(lane.dequeue() == 0);
	ASSERT(lane.count() == 0)
	ASSERT(lane.front() == 0);
	ASSERT(lane.back() == 0);

	// vehicles need to be deleted by us
	delete v1;
	delete v2;
	delete v3;
	delete m1;

    return TR_PASS;
}

/*
Make sure ExpressLane exhibits the same initial state as SimpleLane
*/
TestResult test_ExpressLaneInitialState() {
    ExpressLane lane;

    ASSERT(lane.front() == 0);
    ASSERT(lane.back() == 0);
    ASSERT(lane.dequeue() == 0);
    ASSERT(lane.empty() == true);
    ASSERT(lane.count() == 0);


    return TR_PASS;
}

// made by hamish
TestResult test_ExpressLaneEnqueue() {
    ExpressLane lane;
    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    Vehicle* v2 = new Vehicle(Vehicle::VT_CAR, 2);
    Vehicle* v3 = new Vehicle(Vehicle::VT_BUS, 3);
    Vehicle* m1 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);
    Vehicle* m2 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);

    lane.enqueue(v1);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 1)
    ASSERT(lane.back() == v1);
    ASSERT(lane.front() == v1);
    lane.enqueue(v2);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 2)
    ASSERT(lane.back() == v2);
    ASSERT(lane.front() == v1);
    lane.enqueue(v3);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 3)
    ASSERT(lane.back() == v3);
    ASSERT(lane.front() == v1);
    lane.enqueue(m1);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 4)
    ASSERT(lane.back() == v3);
    ASSERT(lane.front() == m1);
    lane.enqueue(m2);
	ASSERT(!lane.empty())
	ASSERT(lane.count() == 5)
	ASSERT(lane.back() == v3);
	ASSERT(lane.front() == m1);

	ASSERT(lane.dequeue() == m1);
	ASSERT(!lane.empty())
	ASSERT(lane.count() == 4)
	ASSERT(lane.back() == v3);
	ASSERT(lane.front() == m2);
	ASSERT(lane.dequeue() == m2);
	ASSERT(!lane.empty())
	ASSERT(lane.count() == 3)
	ASSERT(lane.back() == v3);
	ASSERT(lane.front() == v1);
	ASSERT(lane.dequeue() == v1);
	ASSERT(!lane.empty())
	ASSERT(lane.count() == 2)
	ASSERT(lane.back() == v3);
	ASSERT(lane.front() == v2);
	ASSERT(lane.dequeue() == v2);
	ASSERT(!lane.empty())
	ASSERT(lane.count() == 1)
	ASSERT(lane.back() == v3);
	ASSERT(lane.front() == v3);
	ASSERT(lane.dequeue() == v3);
	ASSERT(lane.empty())
	ASSERT(lane.count() == 0)
	ASSERT(lane.back() == 0);
	ASSERT(lane.front() == 0);
	ASSERT(lane.dequeue() == 0);

	// vehicles need to be deleted by us
	delete v1;
	delete v2;
	delete v3;
	delete m1;
	delete m2;

    return TR_PASS;
}

// from piazza @418, modified by hamish
TestResult test_ExpressLaneEnqueue2() {
    ExpressLane lane;
    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    Vehicle* v2 = new Vehicle(Vehicle::VT_CAR, 2);
    Vehicle* v3 = new Vehicle(Vehicle::VT_BUS, 3);
    Vehicle* m1 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);

    lane.enqueue(v1);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 1)
    ASSERT(lane.back() == v1);
    ASSERT(lane.front() == v1);
    lane.enqueue(v2);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 2)
    ASSERT(lane.back() == v2);
    ASSERT(lane.front() == v1);
    lane.enqueue(v3);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 3)
    ASSERT(lane.back() == v3);
    ASSERT(lane.front() == v1);
    lane.enqueue(m1);
    ASSERT(!lane.empty())
    ASSERT(lane.count() == 4)
    ASSERT(lane.back() == v3);
    ASSERT(lane.front() == m1);

    ExpressLane lane2;
    Vehicle* v4 = new Vehicle(Vehicle::VT_CAR, 1);
    Vehicle* m2 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);

    lane2.enqueue(v4);
    ASSERT(!lane2.empty())
    ASSERT(lane2.count() == 1)
    ASSERT(lane2.back() == v4);
    ASSERT(lane2.front() == v4);
    lane2.enqueue(m2);
    ASSERT(!lane2.empty())
    ASSERT(lane2.count() == 2)
    ASSERT(lane2.back() == v4);
    ASSERT(lane2.front() == m2);

    ExpressLane lane3;
    Vehicle* m3 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);
    Vehicle* m4 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);

    lane3.enqueue(m3);
    ASSERT(!lane3.empty())
    ASSERT(lane3.count() == 1)
    ASSERT(lane3.back() == m3);
    ASSERT(lane3.front() == m3);
    lane3.enqueue(m4);
    ASSERT(!lane3.empty())
    ASSERT(lane3.count() == 2);
    ASSERT(lane3.back() == m4);
    ASSERT(lane3.front() == m3);

    ExpressLane lane4;
    Vehicle* v5 = new Vehicle(Vehicle::VT_CAR, 1);
    Vehicle* v6 = new Vehicle(Vehicle::VT_CAR, 2);
    Vehicle* m5 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);
    Vehicle* m6 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);

    lane4.enqueue(v5);
    ASSERT(!lane4.empty())
    ASSERT(lane4.count() == 1)
    ASSERT(lane4.back() == v5);
    ASSERT(lane4.front() == v5);
    lane4.enqueue(m5);
    ASSERT(!lane4.empty())
    ASSERT(lane4.count() == 2)
    ASSERT(lane4.back() == v5);
    ASSERT(lane4.front() == m5);
    lane4.enqueue(v6);
    ASSERT(!lane4.empty())
    ASSERT(lane4.count() == 3)
    ASSERT(lane4.back() == v6);
    ASSERT(lane4.front() == m5);
    lane4.enqueue(m6);
    ASSERT(!lane4.empty())
    ASSERT(lane4.count() == 4)
    ASSERT(lane4.back() == v6);
    ASSERT(lane4.front() == m5);

    ASSERT(lane4.dequeue() == m5);
    ASSERT(lane4.dequeue() == m6);

    // vehicles should be deleted by the lane except m5 and m6
    delete m5;
    delete m6;

    return TR_PASS;
}

#endif /*ENABLE_T1_TESTS*/

#ifdef ENABLE_T2_TESTS
/*
Test Intersection construction and initial state.
*/
TestResult test_IntersectionConstruction() {
    Intersection* intersection = new Intersection();
    // check the intersection is initially invalid
    ASSERT(!intersection->valid());
    // invoke the destructor (if any)
    delete intersection;

    return TR_PASS;
}

/*
Test intersection Lane overwriting behavior; i.e. when a new Lane is assigned in a position already occupied by another
Lane connected to the Intersection.
*/
TestResult test_IntersectionOverwrite() {
    Intersection intersection;

    Lane* l1 = new SimpleLane();
    Lane* l2 = new SimpleLane();
    Lane* l3 = new SimpleLane();
    Lane* l4 = new SimpleLane();
    Lane* l5 = new SimpleLane();

    // connect first lanes
    ASSERT(intersection.connectNorth(l1, Intersection::LD_INCOMING) == 0);
    ASSERT(!intersection.valid());
    ASSERT(intersection.connectEast(l2, Intersection::LD_OUTGOING) == 0);
    ASSERT(!intersection.valid());
    ASSERT(intersection.connectSouth(l3, Intersection::LD_INCOMING) == 0);
    ASSERT(!intersection.valid());
    ASSERT(intersection.connectWest(l4, Intersection::LD_OUTGOING) == 0);
    ASSERT(intersection.valid());

    // assign a new lane for each direction
    ASSERT(intersection.connectNorth(l5, Intersection::LD_INCOMING) == l1);
    ASSERT(intersection.valid());
    ASSERT(intersection.connectEast(l5, Intersection::LD_OUTGOING) == l2);
    ASSERT(intersection.valid());
    ASSERT(intersection.connectSouth(l5, Intersection::LD_INCOMING) == l3);
    ASSERT(intersection.valid());
    ASSERT(intersection.connectWest(l5, Intersection::LD_OUTGOING) == l4);
    ASSERT(intersection.valid());

    // de-assign all lanes
    ASSERT(intersection.connectNorth(0, Intersection::LD_INCOMING) == l5);
    ASSERT(!intersection.valid());
    ASSERT(intersection.connectEast(0, Intersection::LD_OUTGOING) == l5);
    ASSERT(!intersection.valid());
    ASSERT(intersection.connectSouth(0, Intersection::LD_INCOMING) == l5);
    ASSERT(!intersection.valid());
    ASSERT(intersection.connectWest(0, Intersection::LD_OUTGOING) == l5);
    ASSERT(!intersection.valid());

    delete l1;
    delete l2;
    delete l3;
    delete l4;
    delete l5;

    return TR_PASS;
}

/*
Test an intersection with four Lanes attached, one incoming and three outgoing. This should be the simplest intersection
it is possible to create; no give way rules have to be applied. Only tested using the SimpleLane class, so motorcycle
filtering behavior shouldn't affect this test.
*/
TestResult test_IntersectionOneIn() {
    Intersection intersection;

    // vehicles for testing
    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    v1->turnLeft();
    Vehicle* v2 = new Vehicle(Vehicle::VT_BUS, 10);
    v2->turnRight();
    Vehicle* v3 = new Vehicle(Vehicle::VT_CAR, 1);
    v3->turnStraight();
    Vehicle* v4 = new Vehicle(Vehicle::VT_MOTORCYCLE, 2);
    v4->turnLeft();
    v4->turnRight();

    // create the RoadWays
    Lane* roadIn = new SimpleLane();
    roadIn->enqueue(v1);
    roadIn->enqueue(v2);
    roadIn->enqueue(v3);
    roadIn->enqueue(v4);

    Lane* roadLeft = new SimpleLane();
    Lane* roadStraight = new SimpleLane();
    Lane* roadRight = new SimpleLane();

    // add RoadWays to the Intersection
    ASSERT(intersection.connectNorth(roadIn, Intersection::LD_INCOMING) == 0); // entry
    ASSERT(intersection.connectEast(roadLeft, Intersection::LD_OUTGOING) == 0); // exit left
    ASSERT(intersection.connectSouth(roadStraight, Intersection::LD_OUTGOING) == 0); // exit straight
    ASSERT(intersection.connectWest(roadRight, Intersection::LD_OUTGOING) == 0); // exit right
    // check intersection is valid
    ASSERT(intersection.valid());

    // simulate a single tick
    intersection.simulate();
    // check results (only one vehicle should proceed)
    ASSERT(roadIn->front() == v2);
    ASSERT(roadLeft->front() == v1);
    ASSERT(roadRight->empty());
    ASSERT(roadStraight->empty());

    // run the simulation for 3 more ticks to allow the other vehicles to proceed
    for (int i = 0; i < 3; ++i) {
        intersection.simulate();
    }

    // check all vehicles passed through the intersection successfully
    ASSERT(roadIn->front() == 0);
    ASSERT(roadLeft->dequeue() == v1);
    ASSERT(roadLeft->dequeue() == v4);
    ASSERT(roadLeft->front() == 0);
    ASSERT(roadStraight->dequeue() == v3);
    ASSERT(roadStraight->front() == 0);
    ASSERT(roadRight->dequeue() == v2);
    ASSERT(roadRight->front() == 0);

    delete roadIn;
    delete roadLeft;
    delete roadStraight;
    delete roadRight;

    delete v1;
    delete v2;
    delete v3;
    delete v4;

    return TR_PASS;
}

/*
Test an intersection with four Lanes attached, two incoming and two outgoing, arranged so that Lanes attached to the
intersection in the same direction (e.g. incoming) are directly opposite each other.
*/
TestResult test_IntersectionTwoInOpposing() {
    Intersection intersection;

    // vehicles for testing
    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    v1->turnLeft();
    Vehicle* v2 = new Vehicle(Vehicle::VT_BUS, 10);
    v2->turnRight();
    Vehicle* v3 = new Vehicle(Vehicle::VT_CAR, 1);
    v3->turnRight();
    Vehicle* v4 = new Vehicle(Vehicle::VT_MOTORCYCLE, 2);
    v4->turnLeft();
    v4->turnRight();
    Vehicle* v5 = new Vehicle(Vehicle::VT_CAR, 3);
    v5->turnRight();
    Vehicle* v6 = new Vehicle(Vehicle::VT_CAR, 2);
    v6->turnRight();
    v6->turnLeft();
    Vehicle* v7 = new Vehicle(Vehicle::VT_BUS, 8);
    v7->turnRight();
    Vehicle* v8 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);
    v8->turnLeft();

    // create the Lanes
    Lane* roadInNorth = new SimpleLane();
    roadInNorth->enqueue(v1);
    roadInNorth->enqueue(v2);
    roadInNorth->enqueue(v3);
    roadInNorth->enqueue(v4);

    Lane* roadInSouth = new SimpleLane();
    roadInSouth->enqueue(v5);
    roadInSouth->enqueue(v6);
    roadInSouth->enqueue(v7);
    roadInSouth->enqueue(v8);

    Lane* roadOutEast = new SimpleLane();
    Lane* roadOutWest = new SimpleLane();

    // add Lanes to the Intersection
    ASSERT(intersection.connectNorth(roadInNorth, Intersection::LD_INCOMING) == 0); // entry
    ASSERT(intersection.connectEast(roadOutEast, Intersection::LD_OUTGOING) == 0); // exit
    ASSERT(intersection.connectSouth(roadInSouth, Intersection::LD_INCOMING) == 0); // entry
    ASSERT(intersection.connectWest(roadOutWest, Intersection::LD_OUTGOING) == 0); // exit
    // check intersection is valid
    ASSERT(intersection.valid());

    // simulate a single tick
    intersection.simulate();
    // check results (exactly one vehicle should proceed)
    ASSERT(roadInNorth->front() == v2);
    ASSERT(roadOutEast->front() == v1);
    ASSERT(roadInSouth->front() == v5);
    ASSERT(roadOutWest->front() == 0);

    // run the simulation for 5 more ticks to allow the other vehicles to proceed (should be enough if road rules are
    // followed)
    for (int i = 0; i < 5; ++i) {
        intersection.simulate();
    }

    // check all vehicles passed through the intersection successfully
    // check inbound lanes
    ASSERT(roadInNorth->front() == 0);
    ASSERT(roadInSouth->front() == 0);
    // check eastbound out lane
    ASSERT(roadOutEast->dequeue() == v1);
    ASSERT(roadOutEast->dequeue() == v5);
    ASSERT(roadOutEast->dequeue() == v6);
    ASSERT(roadOutEast->dequeue() == v4);
    ASSERT(roadOutEast->dequeue() == v7);
    ASSERT(roadOutEast->dequeue() == 0);
    // check westbound out lane
    ASSERT(roadOutWest->dequeue() == v2);
    ASSERT(roadOutWest->dequeue() == v3);
    ASSERT(roadOutWest->dequeue() == v8);
    ASSERT(roadOutWest->dequeue() == 0);

    delete roadInNorth;
    delete roadOutEast;
    delete roadInSouth;
    delete roadOutWest;

    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    delete v6;
    delete v7;
    delete v8;

    return TR_PASS;
}

// from piazza @418
TestResult test_IntersectionTwoInAdjacent() {
    Intersection intersection;

    // vehicles for testing
    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    v1->turnStraight();
    Vehicle* v2 = new Vehicle(Vehicle::VT_BUS, 10);
    v2->turnLeft();
    Vehicle* v3 = new Vehicle(Vehicle::VT_CAR, 1);
    v3->turnStraight();
    Vehicle* v4 = new Vehicle(Vehicle::VT_MOTORCYCLE, 2);
    v4->turnLeft();
    Vehicle* v5 = new Vehicle(Vehicle::VT_CAR, 3);
    v5->turnStraight();
    Vehicle* v6 = new Vehicle(Vehicle::VT_CAR, 2);
    v6->turnStraight();
    Vehicle* v7 = new Vehicle(Vehicle::VT_BUS, 8);
    v7->turnRight();
    Vehicle* v8 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);
    v8->turnStraight();

    // create the Lanes
    Lane* roadInSouth = new SimpleLane();
    roadInSouth->enqueue(v1);
    roadInSouth->enqueue(v2);
    roadInSouth->enqueue(v3);
    roadInSouth->enqueue(v4);

    Lane* roadInEast = new SimpleLane();
    roadInEast->enqueue(v5);
    roadInEast->enqueue(v6);
    roadInEast->enqueue(v7);
    roadInEast->enqueue(v8);

    Lane* roadOutNorth = new SimpleLane();
    Lane* roadOutWest = new SimpleLane();

    // add Lanes to the Intersection
    ASSERT(intersection.connectNorth(roadOutNorth, Intersection::LD_OUTGOING) == 0); // exit
    ASSERT(intersection.connectEast(roadInEast, Intersection::LD_INCOMING) == 0); // entry
    ASSERT(intersection.connectSouth(roadInSouth, Intersection::LD_INCOMING) == 0); // entry
    ASSERT(intersection.connectWest(roadOutWest, Intersection::LD_OUTGOING) == 0); // exit
    // check intersection is valid
    ASSERT(intersection.valid());

    // simulate a single tick
    intersection.simulate();
    // check results (exactly one vehicle should proceed)
    ASSERT(roadInSouth->front() == v2);
    ASSERT(roadInEast->front() == v6);
    ASSERT(roadOutNorth->front() == v1);
    ASSERT(roadOutWest->front() == v5);


    // run the simulation for 7 more ticks to allow the other vehicles to proceed (should be enough if road rules are
    // followed)
    for (int i = 0; i < 8; ++i) {
        intersection.simulate();
    }

    // check all vehicles passed through the intersection successfully
    // check inbound lanes
    ASSERT(roadInEast->front() == 0);
    ASSERT(roadInSouth->front() == 0);
    // check northbound out lane
    ASSERT(roadOutNorth->dequeue() == v1);
    ASSERT(roadOutNorth->dequeue() == v3);
    ASSERT(roadOutNorth->dequeue() == v7);
    ASSERT(roadOutNorth->dequeue() == 0);
    // check westbound out lane
    ASSERT(roadOutWest->dequeue() == v5);
    ASSERT(roadOutWest->dequeue() == v6);
    ASSERT(roadOutWest->dequeue() == v2);
    ASSERT(roadOutWest->dequeue() == v4);
    ASSERT(roadOutWest->dequeue() == v8);
    ASSERT(roadOutWest->dequeue() == 0);

    delete roadInEast;
    delete roadOutNorth;
    delete roadInSouth;
    delete roadOutWest;

    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    delete v6;
    delete v7;
    delete v8;

    return TR_PASS;
}

// from piazza @418, modified by hamish
TestResult test_IntersectionThreeIn() {
    Intersection intersection;

    // vehicles for testing
    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    v1->turnLeft();
    Vehicle* v2 = new Vehicle(Vehicle::VT_BUS, 10);
    v2->turnLeft();
    Vehicle* v3 = new Vehicle(Vehicle::VT_CAR, 1);
    v3->turnLeft();
    Vehicle* v4 = new Vehicle(Vehicle::VT_MOTORCYCLE, 2);
    v4->turnStraight();
    Vehicle* v5 = new Vehicle(Vehicle::VT_CAR, 3);
    v5->turnStraight();
    Vehicle* v6 = new Vehicle(Vehicle::VT_CAR, 2);
    v6->turnStraight();
    Vehicle* v7 = new Vehicle(Vehicle::VT_BUS, 8);
    v7->turnRight();
    Vehicle* v8 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);
    v8->turnRight();
    Vehicle* v9 = new Vehicle(Vehicle::VT_MOTORCYCLE, 1);
    v9->turnRight();

    // create the Lanes
    Lane* roadInSouth = new SimpleLane();
    roadInSouth->enqueue(v1);
    roadInSouth->enqueue(v2);
    roadInSouth->enqueue(v3);

    Lane* roadInEast = new SimpleLane();
    roadInEast->enqueue(v4);
    roadInEast->enqueue(v5);
    roadInEast->enqueue(v6);

    Lane* roadInNorth = new SimpleLane();
    roadInNorth->enqueue(v7);
    roadInNorth->enqueue(v8);
    roadInNorth->enqueue(v9);

    Lane* roadOutWest = new SimpleLane();

    // add Lanes to the Intersection
    ASSERT(intersection.connectNorth(roadInNorth, Intersection::LD_INCOMING) == 0); // entry
    ASSERT(intersection.connectEast(roadInEast, Intersection::LD_INCOMING) == 0); // entry
    ASSERT(intersection.connectSouth(roadInSouth, Intersection::LD_INCOMING) == 0); // entry
    ASSERT(intersection.connectWest(roadOutWest, Intersection::LD_OUTGOING) == 0); // exit
    // check intersection is valid
    ASSERT(intersection.valid());

    // simulate a single tick
    intersection.simulate();
    // check results (exactly one vehicle should proceed)
    ASSERT(roadInSouth->front() == v1);
    ASSERT(roadInEast->front() == v5);
    ASSERT(roadInNorth->front() == v7);
    ASSERT(roadOutWest->front() == v4);

    // run the simulation for 9 more ticks to allow the other vehicles to proceed (should be enough if road rules are
    // followed)
    for (int i = 0; i < 9; ++i) {
        intersection.simulate();
    }

    // check all vehicles passed through the intersection successfully
    // check inbound lanes
    ASSERT(roadInEast->front() == 0);
    ASSERT(roadInSouth->front() == 0);
    ASSERT(roadInNorth->front() == 0);
    // check westbound out lane
    ASSERT(roadOutWest->dequeue() == v4);
    ASSERT(roadOutWest->dequeue() == v5);
    ASSERT(roadOutWest->dequeue() == v6);
    ASSERT(roadOutWest->dequeue() == v1);
    ASSERT(roadOutWest->dequeue() == v2);
    ASSERT(roadOutWest->dequeue() == v3);
    ASSERT(roadOutWest->dequeue() == v7);
    ASSERT(roadOutWest->dequeue() == v8);
    ASSERT(roadOutWest->dequeue() == v9);
    ASSERT(roadOutWest->dequeue() == 0);

    delete roadInEast;
    delete roadInNorth;
    delete roadInSouth;
    delete roadOutWest;

    delete v1;
    delete v2;
    delete v3;
    delete v4;
    delete v5;
    delete v6;
    delete v7;
    delete v8;
    delete v9;

    return TR_PASS;
}

// made by hamish
TestResult test_TrafficNetwork() {

	Intersection i1, i2, i3, i4;
	Lane *lanes[12];
	for (int i=0; i<12; i++) lanes[i] = new ExpressLane();

	i1.connectNorth(lanes[0], Intersection::LD_INCOMING);
	i1.connectEast(lanes[3], Intersection::LD_OUTGOING);
	i1.connectSouth(lanes[5], Intersection::LD_INCOMING);
	i1.connectWest(lanes[2], Intersection::LD_INCOMING);

	i2.connectNorth(lanes[1], Intersection::LD_INCOMING);
	i2.connectEast(lanes[4], Intersection::LD_OUTGOING);
	i2.connectSouth(lanes[6], Intersection::LD_OUTGOING);
	i2.connectWest(lanes[3], Intersection::LD_INCOMING);

	i3.connectNorth(lanes[6], Intersection::LD_INCOMING);
	i3.connectEast(lanes[9], Intersection::LD_OUTGOING);
	i3.connectSouth(lanes[11], Intersection::LD_OUTGOING);
	i3.connectWest(lanes[8], Intersection::LD_OUTGOING);

	i4.connectNorth(lanes[5], Intersection::LD_OUTGOING);
	i4.connectEast(lanes[8], Intersection::LD_INCOMING);
	i4.connectSouth(lanes[10], Intersection::LD_OUTGOING);
	i4.connectWest(lanes[7], Intersection::LD_INCOMING);

	/* Test with a single car to go around the loop */

	Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
	v1->turnLeft();
	v1->turnRight();
	v1->turnRight();
	v1->turnRight();
	v1->turnRight();
	v1->turnStraight();
	lanes[0]->enqueue(v1);

	i1.simulate();
	i2.simulate();
	i3.simulate();
	i4.simulate();
	i1.simulate();
	i2.simulate();

	for (int i=0; i<12; i++) {
		ASSERT(i == 4 || lanes[i]->dequeue() == 0);
	}
	ASSERT(lanes[4]->dequeue() == v1);
	ASSERT(v1->nextTurn() == Vehicle::TD_INVALID);

	delete v1;
	for (int i=0; i<12; i++) delete lanes[i];

	return TR_PASS;
}

// from piazza @418
TestResult test_TrafficNetwork2() {
    Intersection i0;
    Intersection i1;
    Intersection i2;
    Intersection i3;

    Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
    v1->turnLeft();
    v1->turnStraight();
    Vehicle* v2 = new Vehicle(Vehicle::VT_BUS, 10);
    v2->turnStraight();
    v2->turnRight();
    v2->turnLeft();
    Vehicle* v3 = new Vehicle(Vehicle::VT_CAR, 1);
    v3->turnStraight();
    v3->turnRight();
    v3->turnLeft();
    Vehicle* v4 = new Vehicle(Vehicle::VT_MOTORCYCLE, 2);
    v4->turnLeft();
    v4->turnRight();
    v4->turnRight();
    v4->turnRight();
    v4->turnRight();
    v4->turnRight();
    v4->turnRight();
    v4->turnStraight();

    Lane* lanes[12];
    for (int i=0;i<12;i++) {
    	lanes[i] = new SimpleLane();
    }

    lanes[0]->enqueue(v1);
    lanes[1]->enqueue(v2);
    lanes[2]->enqueue(v3);
    lanes[7]->enqueue(v4);

    i0.connectNorth(lanes[0], Intersection::LD_INCOMING);
    i0.connectEast(lanes[3], Intersection::LD_OUTGOING);
    i0.connectSouth(lanes[5], Intersection::LD_INCOMING);
    i0.connectWest(lanes[2], Intersection::LD_INCOMING);
    i1.connectNorth(lanes[1], Intersection::LD_INCOMING);
    i1.connectEast(lanes[4], Intersection::LD_OUTGOING);
    i1.connectSouth(lanes[6], Intersection::LD_OUTGOING);
    i1.connectWest(lanes[3], Intersection::LD_INCOMING);
    i2.connectNorth(lanes[5], Intersection::LD_OUTGOING);
    i2.connectEast(lanes[8], Intersection::LD_INCOMING);
    i2.connectSouth(lanes[10], Intersection::LD_OUTGOING);
    i2.connectWest(lanes[7], Intersection::LD_INCOMING);
    i3.connectNorth(lanes[6], Intersection::LD_INCOMING);
    i3.connectEast(lanes[9], Intersection::LD_OUTGOING);
    i3.connectSouth(lanes[11], Intersection::LD_OUTGOING);
    i3.connectWest(lanes[8], Intersection::LD_OUTGOING);

    ASSERT(i0.valid());
    ASSERT(i1.valid());
    ASSERT(i2.valid());
    ASSERT(i3.valid());

    i0.simulate();
    i1.simulate();
    i3.simulate();
    i2.simulate();
    ASSERT(lanes[0]->front() == v1);
    ASSERT(lanes[10]->front() == v2);
    ASSERT(lanes[3]->front() == v3);
    ASSERT(lanes[5]->front() == v4);

    i0.simulate();
    i1.simulate();
    i3.simulate();
    i2.simulate();
    ASSERT(lanes[3]->front() == v1);
    ASSERT(lanes[10]->front() == v2);
    ASSERT(lanes[9]->front() == v3);
    ASSERT(lanes[5]->front() == v4);

    i0.simulate();
    i1.simulate();
    i3.simulate();
    i2.simulate();
    ASSERT(lanes[4]->front() == v1);
    ASSERT(lanes[10]->front() == v2);
    ASSERT(lanes[9]->front() == v3);
    ASSERT(lanes[3]->front() == v4)

    i0.simulate();
    i1.simulate();
    i3.simulate();
    i2.simulate();
    i0.simulate();
    i1.simulate();
    i3.simulate();
    i2.simulate();
    ASSERT(lanes[4]->front() == v1);
    ASSERT(lanes[10]->front() == v2);
    ASSERT(lanes[9]->front() == v3);
    ASSERT(lanes[11]->front() == v4)

    for (int i=0;i<12;i++) {
    	delete lanes[i];
    }

    return TR_PASS;
}

// from piazza @301, modified by hamish
TestResult test_Intersections(){

	// Create Intersections

	Intersection intersection1;
	Intersection intersection2;
	Intersection intersection3;
	Intersection intersection4;

	Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
	v1->turnStraight();
	v1->turnLeft();
	Vehicle* v2 = new Vehicle(Vehicle::VT_BUS, 10);
	v2->turnStraight();
	v2->turnStraight();
	Vehicle* v3 = new Vehicle(Vehicle::VT_CAR, 1);
	v3->turnLeft();
	v3->turnRight();
	v3->turnStraight();
	Vehicle* v4 = new Vehicle(Vehicle::VT_CAR, 1);
	v4->turnStraight();
	v4->turnLeft();

	// Creating first intersection

	Lane* North1 = new SimpleLane();
	North1->enqueue(v2);
	Lane* West1 = new SimpleLane();
	West1->enqueue(v1);
	Lane* roadTop = new SimpleLane();
	Lane* roadLeft = new SimpleLane();


	ASSERT(intersection1.connectNorth(North1, Intersection::LD_INCOMING) == 0);
	ASSERT(intersection1.connectEast(roadTop, Intersection::LD_OUTGOING) == 0);
	ASSERT(intersection1.connectSouth(roadLeft, Intersection::LD_OUTGOING) == 0);
	ASSERT(intersection1.connectWest(West1, Intersection::LD_INCOMING) == 0);

	// Creating second intersection

	Lane* North2 = new SimpleLane();
	Lane* East2 = new SimpleLane();
	East2->enqueue(v3);
	Lane* roadRight = new SimpleLane();

	ASSERT(intersection2.connectNorth(North2, Intersection::LD_OUTGOING) == 0);
	ASSERT(intersection2.connectEast(East2, Intersection::LD_INCOMING) == 0);
	ASSERT(intersection2.connectSouth(roadRight, Intersection::LD_OUTGOING) == 0);
	ASSERT(intersection2.connectWest(roadTop, Intersection::LD_INCOMING) == 0);


	// Creating third intersection

	Lane* South3 = new SimpleLane();
	Lane* East3= new SimpleLane();
	East3->enqueue(v4);
	Lane* roadBot = new SimpleLane();

	ASSERT(intersection3.connectNorth(roadRight, Intersection::LD_INCOMING) == 0);
	ASSERT(intersection3.connectEast(East3, Intersection::LD_INCOMING) == 0);
	ASSERT(intersection3.connectSouth(South3, Intersection::LD_OUTGOING) == 0);
	ASSERT(intersection3.connectWest(roadBot, Intersection::LD_OUTGOING) == 0);

	// Creating fourth intersection

	Lane* South4 = new SimpleLane();
	Lane* West4 = new SimpleLane();

	ASSERT(intersection4.connectNorth(roadLeft, Intersection::LD_INCOMING) == 0);
	ASSERT(intersection4.connectEast(roadBot, Intersection::LD_INCOMING) == 0);
	ASSERT(intersection4.connectSouth(South4, Intersection::LD_OUTGOING) == 0);
	ASSERT(intersection4.connectWest(West4, Intersection::LD_OUTGOING) == 0);

	//cout << "Intersections Created" << endl;
	//cout << "Time to simulate" << endl;

	intersection1.simulate();
	ASSERT(North1->front() == 0);
	ASSERT(West1->front() == 0);
	ASSERT(roadTop->back() == v1);
	ASSERT(roadLeft->back() == v2);


	intersection2.simulate();
	ASSERT(North2->back() == v1);
	ASSERT(East2->front() == 0);
	ASSERT(roadRight->back() == v3);
	ASSERT(roadTop->back() == 0);


	 for (int i=0; i<2; i++){
		 intersection3.simulate();
	 }

	 ASSERT(roadRight->back() == 0);
	ASSERT(East3->back() == 0);
	ASSERT(roadBot->back() == v3);
	ASSERT(roadBot->front() == v4);
	ASSERT(South3->back() == 0);


	 for (int i=0; i<3; i++){
		 intersection4.simulate();
	 }

	 ASSERT(roadLeft->back() == 0);
	 ASSERT(roadBot->back() == 0);
	 ASSERT(South4->front() == v2);
	 ASSERT(South4->back() == v4);
	 ASSERT(West4->back() == v3);

	//cout << "THe Largest Case has been passed" << endl;

	delete North1;
	delete West1;
	delete roadTop;
	delete roadLeft;
	delete North2;
	delete East2;
	delete roadRight;
	delete South3;
	delete East3;
	delete roadBot;
	delete South4;
	delete West4;

	return TR_PASS;
}

//from piazza @376
TestResult test_The_Filip_Simulate() {
	Intersection intersection;
	// vehicles for testing
	Vehicle* v1 = new Vehicle(Vehicle::VT_CAR, 1);
	v1->turnStraight();//v1 turns straight
	Vehicle* v2 = new Vehicle(Vehicle::VT_CAR, 10);
	v2->turnLeft();//v2 turns left
	Vehicle* v3 = new Vehicle(Vehicle::VT_CAR, 1);
	v3->turnRight();//v3 turns right
	Lane* roadInNorth = new SimpleLane();
	roadInNorth->enqueue(v1);//v1 should be in north
	Lane* roadInWest = new SimpleLane();
	roadInWest->enqueue(v3);//v3 should be in west
	Lane* roadInEast = new SimpleLane();
	roadInEast->enqueue(v2);//v2 should be in east
	Lane* roadOutSouth = new SimpleLane();

	ASSERT(intersection.connectNorth(roadInNorth, Intersection::LD_INCOMING) == 0); // entry
	ASSERT(intersection.connectEast(roadInEast, Intersection::LD_INCOMING) == 0); // entry
	ASSERT(intersection.connectSouth(roadOutSouth, Intersection::LD_OUTGOING) == 0); // exit
	ASSERT(intersection.connectWest(roadInWest, Intersection::LD_INCOMING) == 0); // entry
	// check intersection is valid
	ASSERT(intersection.valid());
	//simulate and check results
	intersection.simulate();
	ASSERT(roadInNorth->front() == 0);
	//simulate and check results
	intersection.simulate();
	ASSERT(roadInEast->front() == 0);
	//simulate and run
	intersection.simulate();
	ASSERT(roadInWest->front() == 0);
	ASSERT(roadOutSouth->front() == v1);
	ASSERT(roadOutSouth->dequeue() == v1);
	ASSERT(roadOutSouth->dequeue() == v2);
	ASSERT(roadOutSouth->dequeue() == v3);
	delete roadInNorth;
	delete roadInEast;
	delete roadOutSouth;
	delete roadInWest;
	delete v1;
	delete v2;
	delete v3;
	return TR_PASS;
}

#endif /*ENABLE_T2_TESTS*/

/*
This function collects up all the tests as a vector of function pointers. If you create your own
tests and want to be able to run them, make sure you add them to the `tests` vector here.
*/
vector<TestResult (*)()> generateTests() {
    vector<TestResult (*)()> tests;
#ifdef ENABLE_VEHICLE_TESTS
    tests.push_back(&test_VehicleConstruction);
    tests.push_back(&test_VehicleTurning);
#endif /*ENABLE_VEHICLE_TESTS*/
#ifdef ENABLE_T1_TESTS
    tests.push_back(&test_SimpleLaneConstruction);
    tests.push_back(&test_SimpleLaneInitialState);
    tests.push_back(&test_SimpleLaneEnqueue);
    tests.push_back(&test_SimpleLaneEnqueueModified);
    tests.push_back(&test_SimpleLaneDequeue);
    tests.push_back(&test_ExpressLaneInitialState);
    tests.push_back(&test_ExpressLaneEnqueue);
    tests.push_back(&test_ExpressLaneEnqueue2);
#endif /*ENABLE_T1_TESTS*/
#ifdef ENABLE_T2_TESTS
    tests.push_back(&test_IntersectionConstruction);
    tests.push_back(&test_IntersectionOverwrite);
    tests.push_back(&test_IntersectionOneIn);
    tests.push_back(&test_IntersectionTwoInOpposing);
    tests.push_back(&test_IntersectionTwoInAdjacent);
    tests.push_back(&test_IntersectionThreeIn);
    tests.push_back(&test_TrafficNetwork);
    tests.push_back(&test_TrafficNetwork2);
    tests.push_back(&test_Intersections);
    tests.push_back(&test_The_Filip_Simulate);
#endif /*ENABLE_T2_TESTS*/

    return tests;
}

int main(int argc, char const* argv[]) {

    // If one or more test numbers are passed as command-line parameters, execute them
    vector<TestResult (*)()> tests_to_run = generateTests();
    unsigned int pass_count = 0;
    unsigned int fail_count = 0;
    unsigned int run_count = 0;
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            unsigned int test_num = atoi(argv[i]);
            if (test_num > tests_to_run.size()) {
                cout << "ERROR: unknown test case " << test_num << endl;
                continue;
            }
            // run the test
            ++run_count;
            TestResult result = tests_to_run[test_num]();
            if (result == TR_FAIL) {
                cout << "FAIL: Test " << test_num << " failed." << endl;
                ++fail_count;
            } else {
                cout << "PASS: Test " << test_num << " passed." << endl;
                ++pass_count;
            }
        }
    } else {
        // otherwise, run all tests
        // Make sure to update this section as you add more tests
        // Add the tests for the first task
        for (unsigned int t = 0; t < tests_to_run.size(); ++t) {
            ++run_count;
            TestResult result = tests_to_run[t]();
            if (result == TR_FAIL) {
                cout << "FAIL: Test " << t << " failed." << endl;
                ++fail_count;
            } else {
                cout << "PASS: Test " << t << " passed." << endl;
                ++pass_count;
            }
        }
    }
    cout << "\n-------------------------------------------------\n"
         << "Total Run: " << run_count << "\n"
         << "Total PASSED: " << pass_count << "\n"
         << "Total FAILED: " << fail_count << "\n"
         << "-------------------------------------------------\n" << endl;

    // Return 0 if everything was ok
    return 0;
}
