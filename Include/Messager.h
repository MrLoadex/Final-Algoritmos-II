#ifndef MESSAGER_H
#define MESSAGER_H

#include <iostream>

class Messager {
public:
    virtual void sendMessage(std::string message) = 0;
    virtual void setUser(std::string user) = 0;
    virtual std::string getUser() const = 0;
};

#endif // MESSAGER_H