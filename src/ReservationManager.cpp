#include "ReservationManager.h"
#include <algorithm>
#include <iostream>

std::list<std::shared_ptr<Cubicle>> ReservationManager::getCubicles() const {
    std::list<std::shared_ptr<Cubicle>> cubicleList;
    for (const auto& cubicle : reservedCubicles) {
        cubicleList.push_back(std::make_shared<Cubicle>(cubicle));
    }
    for (const auto& cubicle : freeCubicles) {
        cubicleList.push_back(std::make_shared<Cubicle>(cubicle));
    }
    return cubicleList;
}

std::list<std::shared_ptr<Cubicle>> ReservationManager::getFreeCubicles() const {
    std::list<std::shared_ptr<Cubicle>> freeCubiclesPtr;
    for (const auto& cubicle : freeCubicles) {
        freeCubiclesPtr.push_back(std::make_shared<Cubicle>(cubicle));
    }
    return freeCubiclesPtr;
}

std::list<std::shared_ptr<Cubicle>> ReservationManager::getReservedCubicles() const {
    std::list<std::shared_ptr<Cubicle>> reservedCubiclesPtr;
    for (const auto& cubicle : reservedCubicles) {
        reservedCubiclesPtr.push_back(std::make_shared<Cubicle>(cubicle));
    }
    return reservedCubiclesPtr;
}

void ReservationManager::addCubicle(const Cubicle& cubicle) {
    freeCubicles.push_back(cubicle);
}

void ReservationManager::reserve(std::shared_ptr<Customer> customer, unsigned cubiclesNeeded) {
    std::list<Cubicle> cubs;

    // Comprobar si hay suficientes cubiculos disponibles
    if (freeCubicles.size() < cubiclesNeeded) {
        std::cout << "No hay suficientes cubiculos disponibles." << std::endl;
        return;
    }

    // Reservar los cubiculos y moverlos de freeCubicles a reservedCubicles
    auto it = freeCubicles.begin();
    for (unsigned i = 0; i < cubiclesNeeded; ++i) {
        Cubicle cubicle(it->getId());
        cubs.push_back(cubicle);
        reservedCubicles.push_back(cubicle);
        it = freeCubicles.erase(it);
    }

    reservations.push_back(std::make_shared<Reservation>(customer, cubs));
}

void ReservationManager::endReservation(const std::shared_ptr<Reservation>& reservation) {
    if (reservation) {
        auto it = std::find(reservations.begin(), reservations.end(), reservation);

        if (it != reservations.end()) {
            const std::list<Cubicle>& cubiclesInReservation = reservation->getCubicles();

            freeCubicles.insert(freeCubicles.begin(), cubiclesInReservation.begin(), cubiclesInReservation.end());

            auto cubicle = reservedCubicles.begin();
            while (cubicle != reservedCubicles.end()) {
                bool erased = false;

                for (auto cubRes : cubiclesInReservation) {
                    if (cubRes.getId() == cubicle->getId()) {
                        cubicle = reservedCubicles.erase(cubicle);
                        erased = true;
                        break;
                    }
                }

                if (!erased) {
                    ++cubicle;
                }
            }

            reservations.erase(it);
            Notifier::notify(reservation);
        } else {
            std::cout << "Error: Reservacion no encontrada." << std::endl;
        }
    }
}

std::list<std::shared_ptr<Reservation>> ReservationManager::getReservations() const {
    return reservations;
}

void ReservationManager::addCustomer(Customer _customer) {
    customers.push_back(_customer);
}

std::list<std::shared_ptr<Customer>> ReservationManager::getCustomers() {
    std::list<std::shared_ptr<Customer>> customerPointers;

    for (const auto& customer : customers) {
        std::shared_ptr<Customer> customerPtr = std::make_shared<Customer>(customer);
        customerPointers.push_back(customerPtr);
    }

    return customerPointers;
}
