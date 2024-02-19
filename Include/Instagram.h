#ifndef INSTAGRAM_H
#define INSTAGRAM_H

#include "Messager.h"

class Instagram : public Messager {
private:
    std::string user;

public:
    void sendMessage(std::string message) override;
    void setUser(std::string user) override;
    std::string getUser() const override;
};

#endif // INSTAGRAM_H
