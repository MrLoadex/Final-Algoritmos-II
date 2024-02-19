:: Compilo código objeto
g++ -Wall -std=c++11 -I.\Include -c .\src\Menu.cpp
g++ -Wall -std=c++11 -I.\Include -c .\src\ReservationManager.cpp
g++ -Wall -std=c++11 -I.\Include -c .\src\Reservation.cpp
g++ -Wall -std=c++11 -I.\Include -c .\src\Notifier.cpp
g++ -Wall -std=c++11 -I.\Include -c .\src\Customer.cpp
g++ -Wall -std=c++11 -I.\Include -c .\src\Cubicle.cpp
g++ -Wall -std=c++11 -I.\Include -c .\src\Messager.cpp
g++ -Wall -std=c++11 -I.\Include -c .\src\Whatsapp.cpp
g++ -Wall -std=c++11 -I.\Include -c .\src\Instagram.cpp
g++ -Wall -std=c++11 -I.\Include -c .\src\Facebook.cpp
g++ -Wall -std=c++11 -I.\ -I.\Include\ -c .\bd.cpp


:: Compilo el Binario
g++ Menu.o ReservationManager.o Reservation.o Notifier.o Customer.o Cubicle.o Messager.o Whatsapp.o Instagram.o Facebook.o bd.o -o CubicleAlquiler.exe

:: Limpio los códigos objeto
DEL .\*.o

:: Ejecuto
CubicleAlquiler.exe
