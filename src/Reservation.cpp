#include "Reservation.h"

Reservation::Reservation(std::shared_ptr<Customer> reservationCustomer, std::list<Cubicle> reservationCubicles)
    : customer(reservationCustomer), cubicles(reservationCubicles) {}

std::shared_ptr<Customer> Reservation::getCustomer() const {
    return customer;
}

std::list<Cubicle> Reservation::getCubicles() const {
    return cubicles;
}

void Reservation::setCustomer(const std::shared_ptr<Customer> newCustomer) {
    customer = newCustomer;
}

void Reservation::setCubicles(const std::list<Cubicle> newCubicles) {
    cubicles = newCubicles;
}
