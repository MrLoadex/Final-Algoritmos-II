#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <memory>
#include "Reservation.h"

class Notifier {
private:
    static std::shared_ptr<Customer> getCustomer(std::shared_ptr<Reservation> reservation);
    static std::shared_ptr<Messager> getPreferredMessager(std::shared_ptr<Customer> customer);

public:
    static void notify(std::shared_ptr<Reservation> reservation);
};

#endif // NOTIFIER_H
