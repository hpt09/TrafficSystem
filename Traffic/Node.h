/*
 * Node.h
 *
 *  Created on: Aug 30, 2016
 *      Author: Hpt09
 */

#ifndef TRAFFIC_NODE_H_
#define TRAFFIC_NODE_H_

#include "Vehicle.hpp"

 /* This Node class stores vehicle pointers and stores the pointer to the next node which will contain the pointer to a vehicle at the back.*/
class Node {
private:
	Vehicle *queued;
	Node *next;
public:
	// Creates a new node with the pointer to a vehicle
	Node(Vehicle* v);

	// Sets the pointer to the next node
	void setNext(Node *n);

	// Gets the pointer to the next node
	Node* getNext() const;

	// Gets the pointer to the vehicle the node stores
	Vehicle* getQueued() const;

	// Destorys the node
	virtual ~Node();
};

#endif /* TRAFFIC_NODE_H_ */
