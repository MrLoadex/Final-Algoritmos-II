#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <memory>
#include "Messager.h"

class Customer {
private:
    int id;
    std::string apellido;
    std::shared_ptr<Messager> preferredMessager;

public:
    Customer(int customerId, const std::string customerApellido);
    int getId() const;
    void setId(int newId);
    std::string getApellido() const;
    void setApellido(const std::string newApellido);
    std::shared_ptr<Messager> getPreferredMessager() const;
    void setPreferredMessager(std::shared_ptr<Messager> messager);
    void setUserMessager(std::string customerUser);
};

#endif // CUSTOMER_H
