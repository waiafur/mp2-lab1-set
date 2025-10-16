#pragma once
#include "tset.h" 
class TLight {

	TSet CarLights;
	TSet PedLights;
public:
	TLight(int ped, int car);
	char get(char place);
	void tick();
};
//0- red, 1-green, 2-yellow
int Crypter(char a) {
	switch (a) {
	case 'r':
		return 0;
	case 'g':
		return 1;
	case 'y':
		return 2;
	}
}