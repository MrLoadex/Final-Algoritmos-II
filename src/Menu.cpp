#include <iostream>
#include "menu.h"
#include <ReservationManager.h>
#include <Notifier.h>
#include <Reservation.h>
#include <Customer.h>
#include <Cubicle.h>
#include <Messager.h>
#include <Facebook.h>
#include <Instagram.h>
#include <Whatsapp.h>



void Menu::showMenu() {
    int option;
    do {
        cout << "\n*** Menu de la Aplicacion ***" << endl;
        cout << "1. Crear Cliente" << endl;
        cout << "2. Cargar Cubiculos" << endl;
        cout << "3. Reservar Cubiculos" << endl;
        cout << "4. Mostrar Cubiculos Libres" << endl;
        cout << "5. Mostrar Cubiculos Alquilados" << endl;
        cout << "6. Mostrar Reservas" << endl;
        cout << "7. Finalizar reserva" << endl;
        cout << "0. Salir" << endl;

        cout << "Ingrese la opcion deseada: ";
        cin >> option;

        switch (option) {
            case 1:
                createCustomer();
                break;
            case 2:
                loadCubicles();
                break;
            case 3:
                reserveCubicles();
                break;
            case 4:
                showFreeCubicles();
                break;
            case 5:
                showRentedCubicles();
                break;
            case 6:
                showReservations();
                break;
            case 7:
                endReservation();
                break;
            case 0:
                cout << "Saliendo de la aplicacion. Hasta luego!" << endl;
                break;
            default:
                cout << "Opcion no valida. Intentelo de nuevo." << endl;
        }

        // Limpiar el buffer de entrada
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Pausar para que el usuario pueda ver los resultados antes de volver al menu
        cout << "\nPresiona Enter para continuar...";
        cin.ignore();
        system("clear || cls");  // Limpiar la pantalla de la consola

    } while (option != 0);
}

void Menu::createCustomer() 
{
    int customerId;
    string apellido;
    string userName;
    int messengerChoice;

    cout << "Ingrese el ID del cliente: ";
    cin >> customerId;

    cout << "Ingrese el apellido del cliente: ";
    cin >> apellido;

    cout << "Seleccione el mensajero preferido:" << endl;
    cout << "1. Facebook" << endl;
    cout << "2. Instagram" << endl;
    cout << "3. Whatsapp" << endl;
    cout << "Seleccione una opcion: ";
    cin >> messengerChoice;
    
    cout << "Ingrese su nombre de usuario: ";
    cin >> userName;

    shared_ptr<Messager> preferredMessager;

    switch (messengerChoice) {
        case 1:
            preferredMessager = make_shared<Facebook>();
            break;
        case 2:
            preferredMessager = make_shared<Instagram>();
            break;
        case 3:
            preferredMessager = make_shared<Whatsapp>();
            break;
        default:
            cout << "Opcion no valida. Se utilizara Facebook por defecto." << endl;
            preferredMessager = make_shared<Facebook>();
    }
    preferredMessager->setUser(userName);

    Customer newCustomer(customerId, apellido);
    newCustomer.setPreferredMessager(preferredMessager);
    app.addCustomer(newCustomer);

    cout << "Cliente creado exitosamente." << endl;
}

void Menu::loadCubicles() 
{
    //Tomar el ultimo id agregado.
    int lastId;

    if (!app.getCubicles().empty())
    {
        lastId = app.getCubicles().back()->getId() + 1;
    }
    else lastId = 1;
    int newCubicles;
    cout << "Ingrese la cantidad de cubiculos que desea cargar: " << endl;
    cin >> newCubicles;
    for (int i = 0; i< newCubicles; i++)
    {
        Cubicle cubicle(lastId + i);
        app.addCubicle(cubicle);
    }

}

void Menu::reserveCubicles() 
{
    unsigned customerId, cubiclesNeeded;

    shared_ptr<Customer> customer = nullptr; // Puntero al cliente de la app
    
    list<shared_ptr<Customer>> customers; // Lista de clientes de la app

    // Comprobar si hay clientes cargados
    if (!app.getCustomers().empty())
    {
        // Cargar los clientes a la lista local
        customers = app.getCustomers();
        
        // Mostrar datos de los clientes en pantalla
        for (auto customer : customers)
        {
            cout << "Cliente ID: " << customer->getId() << endl
                << "Apellido: " << customer->getApellido()<< endl;
        }
    }
    else
    {
        cout << "ERROR: No hay clientes cargados en el sistema. Debe cargar al menos un cliente antes de seguir" << endl;
        return;
    }
    
    cout << "Ingrese el ID del cliente que desea hacer la reserva: ";
    cin >> customerId;
    
    // Apuntar al cliente espesifico
    for (auto cliente : customers)
    {
        if (cliente->getId() == customerId)
        {
            customer = cliente;
        }
    }

    // Comprobar si la id del cliente es correcta
    if (customer == nullptr)
    {
        cout << "ERROR: ID inexistente." << endl;
        return;
    }

    cout << "Cubiculos disponibles: " << app.getFreeCubicles().size() << endl;
    cout << "Ingrese la cantidad de cubiculos que desea reservar: ";
    cin >> cubiclesNeeded;

    app.reserve(customer, cubiclesNeeded);

    cout << "Reserva realizada exitosamente." << endl;
}

void Menu::showFreeCubicles()
{
    
    cout << "Cubiculos disponibles" << endl;

    auto cubicles = app.getFreeCubicles();
    for (auto cubicle : cubicles)
    {
        cout << "Cubiculo ID: " << cubicle->getId() << endl;
    }
}

void Menu::showRentedCubicles() 
{
    cout << "Cubiculos Alquilados" << endl;

    auto cubicles = app.getReservedCubicles();
    for (auto cubicle : cubicles)
    {
        cout << "Cubiculo ID: " << cubicle->getId() << endl;
    }
}

void Menu::showReservations() 
{
    int index = 1;
    auto reservations = app.getReservations();
    
    cout << "Reservas: " << endl;
    
    for (auto reservation : reservations)
    {
        cout << "Reserva numero: " << index << endl
                << "Cliente ID: " << reservation->getCustomer()->getId() << endl
                << "Apellido: " << reservation->getCustomer()->getApellido() << endl
                << "Cubiculos reservados : " << reservation->getCubicles().size() << endl
                << "Cubiculos ID: ";
                for (auto cubicle : reservation->getCubicles())
                {
                cout << cubicle.getId() << ", ";
                }
                cout << endl;
                index++;
    }

}

void Menu::endReservation()
{
    int iResEnd;
    auto reservations = app.getReservations();
    cout << "Finalizar reservas" << endl;
    
    showReservations();
    cout << endl << "Seleccione la reserva que desea finalizar: ";
    cin >> iResEnd;
    iResEnd--;

    auto reservation = reservations.begin();
    advance(reservation, iResEnd);

    if (reservation != reservations.end()) {
        //Finalizar la reserva
        app.endReservation(*reservation);
    } else {
        cout << "Índice fuera de rango." << endl;
    }

}
