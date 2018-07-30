#include "Vehicle.hpp"

Vehicle::Vehicle(Type newType, unsigned int occupantCount) : vehicleType(newType), occupants(occupantCount) {
}

Vehicle::Type Vehicle::type() const {
    return this->vehicleType;
}

unsigned int Vehicle::occupantCount() const {
    return this->occupants;
}

Vehicle::TurnDirection Vehicle::nextTurn() const {
    // Handle case where turn queue is empty; return TD_INVALID by default.
    if (this->turns.empty()) {
        return TD_INVALID;
    }
    return this->turns.front();
}

Vehicle::TurnDirection Vehicle::makeTurn() {
    // Return TD_INVALID by default
    TurnDirection td = TD_INVALID;
    // Make sure turn queue is not empty
    if (!this->turns.empty()) {
        td = this->turns.front();
        this->turns.pop();
    }
    return td;
}

void Vehicle::turnLeft() {
    this->turns.push(TD_LEFT);
}

void Vehicle::turnRight() {
    this->turns.push(TD_RIGHT);
}

void Vehicle::turnStraight() {
    this->turns.push(TD_STRAIGHT);
}