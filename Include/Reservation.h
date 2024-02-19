#ifndef RESERVATION_H
#define RESERVATION_H

#include <memory>
#include <list>
#include "Cubicle.h"
#include "Customer.h"

class Reservation {
private:
    std::shared_ptr<Customer> customer;
    std::list<Cubicle> cubicles;

public:
    Reservation(std::shared_ptr<Customer> reservationCustomer, std::list<Cubicle> reservationCubicles);
    std::shared_ptr<Customer> getCustomer() const;
    std::list<Cubicle> getCubicles() const;
    void setCustomer(const std::shared_ptr<Customer> newCustomer);
    void setCubicles(const std::list<Cubicle> newCubicles);
};

#endif // RESERVATION_H
