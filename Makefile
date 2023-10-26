all:
	g++ -std=c++11 -mlibscl main.cpp -o !RunImage,ff8 -I/$GCCSDK_INSTALL_ENV/include -L$GCCSDK_INSTALL_ENV/lib

