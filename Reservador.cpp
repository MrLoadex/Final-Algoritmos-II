#include <iostream>
#include <list>
#include <memory>
#include <algorithm>

using namespace std;

class Messager {
public:
    virtual void sendMessage(string message) = 0;
    virtual void setUser(string user) = 0;
    virtual string getUser() const = 0;
};

class Facebook : public Messager {
private:
    string user;

public:
    void sendMessage(string message) override {
        cout << "User: " << user << endl
             << "Mensaje: " << message << endl
             << "Mensaje enviado mediante Facebook" << endl;
    }

    void setUser(string user) override {
        this->user = user;
    }

    string getUser() const override {
        return user;
    }
};

class Instagram : public Messager {
private:
    string user;

public:
    void sendMessage(string message) override {
        cout << "User: " << user << endl
             << "Mensaje: " << message << endl
             << "Mensaje enviado mediante Instagram" << endl;
    }

    void setUser(string user) override {
        this->user = user;
    }

    string getUser() const override {
        return user;
    }
};

class Whatsapp : public Messager {
private:
    string user;

public:
    void sendMessage(string message) override {
        cout << "User: " << user << endl
             << "Mensaje: " << message << endl 
             << "Mensaje enviado mediante Whatsapp" << endl;
    }

    void setUser(string user) override {
        this->user = user;
    }

    string getUser() const override {
        return user;
    }
};

class Cubicle {
private:
    int id;

public:
    Cubicle(int cubicleId) : id(cubicleId) {}

    void setId(int _id)
    {
        id = _id;
    }

    int getId() const {
        return id;
    }
};

class Customer {
private:
    int id;
    string apellido;
    shared_ptr<Messager> preferredMessager;

public:
    Customer(int customerId, const string customerApellido)
        : id(customerId), apellido(customerApellido), preferredMessager(nullptr) {}

    int getId() const {
        return id;
    }

    void setId(int newId) {
        id = newId;
    }

    string getApellido() const {
        return apellido;
    }

    void setApellido(const string newApellido) {
        apellido = newApellido;
    }

    shared_ptr<Messager> getPreferredMessager() const {
        return preferredMessager;
    }

    void setPreferredMessager(shared_ptr<Messager> messager) {
        preferredMessager = messager;
    }

    void setUserMessager(string customerUser) {
        preferredMessager->setUser(customerUser);
    }    
};

class Reservation {
private:
    shared_ptr<Customer> customer;
    list<Cubicle> cubicles;

public:
    Reservation(shared_ptr<Customer> reservationCustomer, list<Cubicle> reservationCubicles)
        : customer(reservationCustomer), cubicles(reservationCubicles) {}

    shared_ptr<Customer> getCustomer() const {
        return customer;
    }

    list<Cubicle> getCubicles() const {
        return cubicles;
    }

    void setCustomer(const shared_ptr<Customer> newCustomer) {
        customer = newCustomer;
    }

    void setCubicles(const list<Cubicle> newCubicles) {
        cubicles = newCubicles;
    }
};

class Notifier {
private:
    static shared_ptr<Customer> getCustomer(shared_ptr<Reservation> reservation) {
        return reservation->getCustomer();
    }
    
    static shared_ptr<Messager> getPreferredMessager(shared_ptr<Customer> customer) {
        return customer->getPreferredMessager();
    }
public:
    static void notify(shared_ptr<Reservation> reservation) {
        shared_ptr<Customer> customer = getCustomer(reservation);

        shared_ptr<Messager> messager = getPreferredMessager(customer);

        messager->sendMessage("Alquiler finalizado");
    }
};

class ReservationManager {
private:
    list<Cubicle> reservedCubicles;
    list<Cubicle> freeCubicles;
    list<shared_ptr<Reservation>> reservations;
    list<Customer> customers;

public:
    list<shared_ptr<Cubicle>> getCubicles() const {
        list<shared_ptr<Cubicle>> cubicleList;
        for (const auto& cubicle : reservedCubicles) {
            cubicleList.push_back(make_shared<Cubicle>(cubicle));
        }
        for (const auto& cubicle : freeCubicles) {
            cubicleList.push_back(make_shared<Cubicle>(cubicle));
        }
        return cubicleList;
    }

    list<shared_ptr<Cubicle>> getFreeCubicles() const {
        list<shared_ptr<Cubicle>> freeCubiclesPtr;
        for (const auto& cubicle : freeCubicles) {
            freeCubiclesPtr.push_back(make_shared<Cubicle>(cubicle));
        }
        return freeCubiclesPtr;
    }

    list<shared_ptr<Cubicle>> getReservedCubicles() const {
        list<shared_ptr<Cubicle>> reservedCubiclesPtr;
        for (const auto& cubicle : reservedCubicles) {
            reservedCubiclesPtr.push_back(make_shared<Cubicle>(cubicle));
        }
        return reservedCubiclesPtr;
    }

    list<shared_ptr<Customer>> getCustomers()
    {
        list<shared_ptr<Customer>> customerPointers;

        // Itera sobre la lista de customers y crea shared_ptr para cada uno
        for (const auto& customer : customers) {
            shared_ptr<Customer> customerPtr = make_shared<Customer>(customer);
            customerPointers.push_back(customerPtr);
        }

        return customerPointers;
    }

    list<shared_ptr<Reservation>> getReservations() const {
        return reservations;
    }

    void addCubicle(const Cubicle& cubicle) {
        freeCubicles.push_back(cubicle);
    }

    void addCustomer(Customer _customer)
    {
        customers.push_back(_customer);
    }

    void reserve(shared_ptr<Customer> customer, unsigned cubiclesNeeded) {
        list<Cubicle> cubs;

        // Comprobar si hay suficientes cubiculos disponibles
        if (freeCubicles.size() < cubiclesNeeded) {
            cout << "No hay suficientes cubiculos disponibles." << endl;
            return;
        }

        // Reservar los cubiculos y moverlos de freeCubicles a reservedCubicles
        auto it = freeCubicles.begin();
        for (unsigned i = 0; i < cubiclesNeeded; ++i) {
            Cubicle cubicle(it->getId());
            cubs.push_back(cubicle);
            reservedCubicles.push_back(cubicle); // Crear cubiculo en reservados
            it = freeCubicles.erase(it);  // Eliminar el cubiculo de freeCubicles
        }

        reservations.push_back(make_shared<Reservation>(customer, cubs));
    }
    
    void endReservation(const shared_ptr<Reservation>& reservation) {
        if (reservation) {

            auto it = find(reservations.begin(), reservations.end(), reservation);

            if (it != reservations.end()) {
                // Obtén los cubiculos asociados a la reserva
                const list<Cubicle>& cubiclesInReservation = reservation->getCubicles();

                // Mueve los cubiculos de la lista de reservedCubicles al principio de freeCubicles
                freeCubicles.insert(freeCubicles.begin(), cubiclesInReservation.begin(), cubiclesInReservation.end());
                
                // Elimina los cubiculos asociados a la reserva de reservedCubicles
                auto cubicle = reservedCubicles.begin();
                while (cubicle != reservedCubicles.end())
                {
                    bool erased = false; // Bandera para controlar si se ha eliminado un elemento
                    
                    for (auto cubRes : cubiclesInReservation)
                    {
                        if (cubRes.getId() == cubicle->getId())
                        {
                            cubicle = reservedCubicles.erase(cubicle);
                            erased = true;
                            break; // Salir del bucle interno si se ha eliminado un elemento
                        }
                    }

                    if (!erased) {
                        ++cubicle; // Incrementar el iterador solo si no se ha eliminado un elemento
                    }
                }
                // Elimina la reservacion de la lista
                reservations.erase(it);

                // Notifica al usuario
                Notifier::notify(reservation);
            } else {
                cout << "Error: Reservacion no encontrada." << endl;
            }
        }
    }

};

class Menu {
public:
    void showMenu() {
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

private:
    ReservationManager app;

    void createCustomer() 
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

    void loadCubicles() 
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

    void reserveCubicles() 
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

    void showFreeCubicles()
    {
        
        cout << "Cubiculos disponibles" << endl;

        auto cubicles = app.getFreeCubicles();
        for (auto cubicle : cubicles)
        {
            cout << "Cubiculo ID: " << cubicle->getId() << endl;
        }
    }

    void showRentedCubicles() 
    {
        cout << "Cubiculos Alquilados" << endl;

        auto cubicles = app.getReservedCubicles();
        for (auto cubicle : cubicles)
        {
            cout << "Cubiculo ID: " << cubicle->getId() << endl;
        }
    }

    void showReservations() 
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

    void endReservation()
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
};

int main()
{
    Menu menu;
    menu.showMenu();
    return 0;
}