#ifndef MENU_H
#define MENU_H

#include "ReservationManager.h"
#include "Messager.h"
#include "Facebook.h"
#include "Instagram.h"
#include "WhatsApp.h"
#include <algorithm>

using namespace std;

class Menu {
public:
    void showMenu();

private:
    ReservationManager app;

    void createCustomer();
    void loadCubicles();
    void reserveCubicles();
    void showFreeCubicles();
    void showRentedCubicles();
    void showReservations();
    void endReservation();
};

#endif // MENU_H
