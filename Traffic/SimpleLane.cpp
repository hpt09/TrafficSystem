#include "SimpleLane.hpp"

SimpleLane::SimpleLane() {
	// Initializing variables
	sum = 0;
	frontVehicle = 0;
	lastVehicle = 0;
}

SimpleLane::~SimpleLane() {
	while (frontVehicle != 0) {
		// dequeues all vehicles until no vehicles are left and deletes the vehicle
		delete dequeue();

	}
}

void SimpleLane::enqueue(Vehicle* vehicle) {
	Node *nodeToAdd = new Node(vehicle);
	// Checks if any vehicle has been enqueued before
	// If no vehicles has been enqueued front vehicle's pointer will be NULL and
	// front vehicle and last vehicle will be the vehicle added
	// or else the last vehicles next enqueued will be the new vehicle which will be
	// the new last vehicle and sum of total vehicles is incremented
	if (frontVehicle == 0) {
		frontVehicle = nodeToAdd;
		lastVehicle = nodeToAdd;
	}
	else {
		lastVehicle->setNext(nodeToAdd);
		lastVehicle = nodeToAdd;
	}
	sum++;
}

Vehicle* SimpleLane::dequeue() {
	// If front vehicle's pointer is NULL then no vehicle can be dequeued and NULL is returned
	// If front vehicle's pointer is equal to last vehicle's pointer then that's the last vehicle
	// and both are set to NULL or else front vehicle is now the second enqueued vehicle
	// the front vehicle node is saved and its vehicle is saved so it can be returned and
	// sum of total vehicles is decremented
	if (frontVehicle == 0) {
		return 0;
	}
	Node *nodeToDelete = frontVehicle;
	if (frontVehicle == lastVehicle) {
		frontVehicle = 0;
		lastVehicle = 0;
	}
	else {
		frontVehicle = frontVehicle->getNext();
	}
	Vehicle *toReturn = nodeToDelete->getQueued();
	sum--;
	return toReturn;
}

bool SimpleLane::empty() const {
	// If sum of total vehicles is equal to 0, returns true which means it is empty or else returns false
	if (sum == 0) {
		return true;
	}
	else {
		return false;
	}
}

unsigned int SimpleLane::count() const {
	// returns sum which is incremented and decremented everytime vehicles are enqueued or dequeued
	return sum;
}

const Vehicle* SimpleLane::front() const {
	// If front vehicles pointer is NULL that means no vehicles are enqueued and returns NULL
	// else it returns front vehicles pointer stored in the front vehicle node
	if (frontVehicle != 0) {
		return frontVehicle->getQueued();
	}
	return 0;
}

const Vehicle* SimpleLane::back() const {
	// If last vehicles pointer is NULL that means no vehicles are enqueued and returns NULL
	// else it returns last vehicles pointer stored in the last vehicle node
	if (lastVehicle != 0) {
		return lastVehicle->getQueued();
	}
	return 0;
}
