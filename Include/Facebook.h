#ifndef FACEBOOK_H
#define FACEBOOK_H

#include "Messager.h"

class Facebook : public Messager {
private:
    std::string user;

public:
    void sendMessage(std::string message) override;
    void setUser(std::string user) override;
    std::string getUser() const override;
};

#endif // FACEBOOK_H
