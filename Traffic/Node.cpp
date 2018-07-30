/*
 * Node.cpp
 *
 *  Created on: Aug 30, 2016
 *      Author: Hpt09
 */

#include "Node.h"

 // Initialise the variables, queued is the vehicle pointer which is initialised to pointer parameter passed and pointer to 
 // next node is set to 0 as next is initialised to 0.
Node::Node(Vehicle* v) : queued(v), next(0) {

}

// Set next will make the next variable which stores the pointer to next node to the node pointer passed in parameter.
void Node::setNext(Node* n) {
	next = n;
}

// Get next returns the next variable.
Node* Node::getNext() const {
	return next;
}

// Returns the queued variable which stores the vehicle pointer.
Vehicle* Node::getQueued() const {
	return queued;
}

Node::~Node() {

}

