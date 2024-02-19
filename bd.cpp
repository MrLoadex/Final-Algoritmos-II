#include <iostream>
#include <list>
#include <memory>
#include <algorithm>
//Intente usar <archivo.h> pero tira error al compilar, aunque le pase la direccion.
#include <ReservationManager.h>
#include <Notifier.h>
#include <Reservation.h>
#include <Customer.h>
#include <Cubicle.h>
#include <Messager.h>
#include <Facebook.h>
#include <Instagram.h>
#include <Whatsapp.h>
#include <Menu.h>

using namespace std;

int main()
{
    Menu menu;
    menu.showMenu();
    return 0;
}