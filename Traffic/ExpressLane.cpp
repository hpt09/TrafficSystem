#include "ExpressLane.hpp"

void ExpressLane::enqueue(Vehicle* vehicle) {

	Node *nodeToAdd = new Node(vehicle);

	// If there's no front vehicle then adding car/bus/motorcycle to the front
	if (frontVehicle == 0) {
		frontVehicle = nodeToAdd;
		lastVehicle = nodeToAdd;
	}
	else {
		// If vehicles are in a queue and vehicle being enqueued is motorcycle
		if (nodeToAdd->getQueued()->type() == Vehicle::VT_MOTORCYCLE) {

			// If there are no motocycles in queue which means front vehicle is not motorcycle
			// then add motorcycle to the front
			if (frontVehicle->getQueued()->type() != Vehicle::VT_MOTORCYCLE) {
				nodeToAdd->setNext(frontVehicle);
				frontVehicle = nodeToAdd;
			}
			else {
				Node *ref = frontVehicle;

				//There are bikes in queue and we need to find the last bike in queue
				for (int i = 1; i < sum; i++) {
					if (ref->getNext()->getQueued()->type() == Vehicle::VT_MOTORCYCLE) {
						ref = ref->getNext();
					}
				}

				// Adding to the back of the last bike
				if (ref == lastVehicle) {
					lastVehicle->setNext(nodeToAdd);
					lastVehicle = nodeToAdd;
				}
				else {
					nodeToAdd->setNext(ref->getNext());
					ref->setNext(nodeToAdd);
				}

			}
		}
		// Adding car/bus to the end
		else {
			lastVehicle->setNext(nodeToAdd);
			lastVehicle = nodeToAdd;
		}
	}
	// sum of the total vehicles is incremented
	sum++;
}
