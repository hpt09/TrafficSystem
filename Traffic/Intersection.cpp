#include "Intersection.hpp"
#include "Vehicle.hpp"


Intersection::Intersection() {
	// Initialise the lanes array to store NULL pointers
	for (int i = 0; i < 4; i++) {
		lanes[i] = 0;
	}
}

bool Intersection::valid() {
	// If all pointers in the lanes array are not equal to NULL then return true else returns false
	if (lanes[0] != 0 && lanes[1] != 0 && lanes[2] != 0 && lanes[3] != 0) {
		return true;
	}
	return false;
}

Lane* Intersection::connectNorth(Lane* lane, LaneDirection direction) {
	// Pointer to north lane is stored in the first index of lanes array and its direction is 
	// stored in the first index of laneDirections array
	// The lane ponter stored before is stored in variable temp and is returned.
	Lane* temp = lanes[0];
	lanes[0] = lane;
	laneDirections[0] = direction;
	return temp;
}

Lane* Intersection::connectEast(Lane* lane, LaneDirection direction) {
	// Pointer to east lane is stored in the second index of lanes array and its direction is 
	// stored in the second index of laneDirections array
	// The lane ponter stored before is stored in variable temp and is returned.
	Lane* temp = lanes[1];
	lanes[1] = lane;
	laneDirections[1] = direction;
	return temp;
}

Lane* Intersection::connectSouth(Lane* lane, LaneDirection direction) {
	// Pointer to south lane is stored in the third index of lanes array and its direction is 
	// stored in the third index of laneDirections array
	// The lane ponter stored before is stored in variable temp and is returned.
	Lane* temp = lanes[2];
	lanes[2] = lane;
	laneDirections[2] = direction;
	return temp;
}

Lane* Intersection::connectWest(Lane* lane, LaneDirection direction) {
	// Pointer to west lane is stored in the fourth index of lanes array and its direction is 
	// stored in the fourth index of laneDirections array
	// The lane ponter stored before is stored in variable temp and is returned.
	Lane* temp = lanes[3];
	lanes[3] = lane;
	laneDirections[3] = direction;
	return temp;
}

int enqueueLane(int index, Vehicle::TurnDirection dir) {
	// Finds the index of the outgoing lane. Left will mean incrementing an index where as right will mean decrementing and 
	// straight will mean adding 2 to the index.
	if (dir == Vehicle::TD_LEFT) {
		index++;
	}
	else if (dir == Vehicle::TD_RIGHT) {
		index--;
	}
	else if (dir == Vehicle::TD_STRAIGHT) {
		index = index + 2;
	}
	// Solves the problem of indexes going out of range to invalid indexes.
	if (index > 3) {
		index = index - 4;
	}
	else if (index < 0) {
		index = index + 4;
	}
	return index;

}

void Intersection::simulate() {
	if (valid()) {
		//checking if incoming lanes are filled and storing their indexes and finding how many they are.
		int incomingLanes = 0;
		int incomingIndexes[3] = {};
		int j = 0;
		for (int i = 0; i < 4; i++) {
			if (laneDirections[i] == LD_INCOMING && lanes[i]->empty() == false) {
				incomingLanes++;
				incomingIndexes[j] = i;
				j++;
			}
		}

		if (incomingLanes == 1) {
			// If there is 1 incoming lane the index of it has to be stored in the first index of array incomingIndexes
			int i = incomingIndexes[0];
			Vehicle::TurnDirection stored = lanes[i]->front()->nextTurn();
			// Finds the outgoing index
			j = ::enqueueLane(i, stored);

			// Dequeues lane, Make turns, Enqueues in outgoing lane
			Vehicle* toTurn = lanes[i]->dequeue();
			toTurn->makeTurn();
			lanes[j]->enqueue(toTurn);
		}
		else if (incomingLanes == 2) {
			int outgoingIndexes[2] = {};
			// getting outgoing lanes indexes
			for (int i = 0; i < 2; i++) {
				outgoingIndexes[i] = ::enqueueLane(incomingIndexes[i], lanes[incomingIndexes[i]]->front()->nextTurn());
			}

			// if they have the same turn direction dequeue both the vehicles at the same time and
			// enqueue in respective outgoing lanes
			if (lanes[incomingIndexes[0]]->front()->nextTurn() == lanes[incomingIndexes[1]]->front()->nextTurn()) {
				for (int i = 0; i < 2; i++) {
					Vehicle* toTurn = lanes[incomingIndexes[i]]->dequeue();
					toTurn->makeTurn();
					lanes[outgoingIndexes[i]]->enqueue(toTurn);
				}
			}
			else {
				// check if adjacent configuration or opposite configuration as vehicle can only go straight if adjacent config
				int straightLanes = 0;
				int j = 0;		//straight turn direction index from incoming indexes
				int k = 0;		//left turn direction index from incoming indexes
				for (int i = 0; i < 2; i++) {
					if (lanes[incomingIndexes[i]]->front()->nextTurn() == Vehicle::TD_STRAIGHT) {
						j = i;
						straightLanes++;
					}
					if (lanes[incomingIndexes[i]]->front()->nextTurn() == Vehicle::TD_LEFT) {
						k = i;
					}
				}
				// adjacent configuration
				// Dequeues lane with straight going vehicle, Make turns, Enqueues in outgoing lane
				if (straightLanes > 0) {
					Vehicle* toTurn = lanes[incomingIndexes[j]]->dequeue();
					toTurn->makeTurn();
					lanes[outgoingIndexes[j]]->enqueue(toTurn);
				}
				// opposite configuration
				// Dequeues lane with left turning vehicle , Make turns, Enqueues in outgoing lane
				else {
					Vehicle* toTurn = lanes[incomingIndexes[k]]->dequeue();
					toTurn->makeTurn();
					lanes[outgoingIndexes[k]]->enqueue(toTurn);
				}
			}

		}
		else if (incomingLanes == 3) {
			// If there's 3 incoming lanes, there has to be one vehicle going straight and therefore need to find index of that lane.
			int j;
			for (int i = 0; i < 3; i++) {
				if (lanes[incomingIndexes[i]]->front()->nextTurn() == Vehicle::TD_STRAIGHT) {
					j = i;
				}
			}
			// Dequeues lane with straight going vehicle, Make turns, Enqueues in outgoing lane
			int k = ::enqueueLane(j, lanes[incomingIndexes[j]]->front()->nextTurn());
			Vehicle* toTurn = lanes[incomingIndexes[j]]->dequeue();
			toTurn->makeTurn();
			lanes[k]->enqueue(toTurn);
		}
	}
}
