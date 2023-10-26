buildARC:
	g++ -std=c++11 main.cpp -o test -I/home/gccsdk/env/include/DeskLib -L/home/gccsdk/env/include/lib -lDesk
build:
	g++ -std=c++11 -mlibscl main.cpp -o app -I/home/gccsdk/env/include/DeskLib -L/home/gccsdk/env/include/lib -lDesk-scl

.PHONY: buildARC build
