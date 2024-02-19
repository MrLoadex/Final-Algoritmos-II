#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <list>
#include "Cubicle.h"
#include "Reservation.h"
#include "Customer.h"
#include "Notifier.h"

class ReservationManager {
private:
    std::list<Cubicle> reservedCubicles;
    std::list<Cubicle> freeCubicles;
    std::list<std::shared_ptr<Reservation>> reservations;
    std::list<Customer> customers;

public:
    std::list<std::shared_ptr<Cubicle>> getCubicles() const;
    std::list<std::shared_ptr<Cubicle>> getFreeCubicles() const;
    std::list<std::shared_ptr<Cubicle>> getReservedCubicles() const;
    std::list<std::shared_ptr<Reservation>> getReservations() const;
    std::list<std::shared_ptr<Customer>> getCustomers();
    void addCubicle(const Cubicle& cubicle);
    void addCustomer(Customer _customer);
    void reserve(std::shared_ptr<Customer> customer, unsigned cubiclesNeeded);
    void endReservation(const std::shared_ptr<Reservation>& reservation);
};

#endif // RESERVATION_MANAGER_H
