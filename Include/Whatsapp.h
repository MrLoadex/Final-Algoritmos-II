#ifndef WHATSAPP_H
#define WHATSAPP_H

#include "Messager.h"

using namespace std;

class Whatsapp : public Messager {
private:
    string user;

public:
    void sendMessage(string message) override;
    void setUser(string user) override;
    string getUser() const override;
};

#endif // WHATSAPP_H
