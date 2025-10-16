#include "Light.h"
TLight::TLight(int ped, int car) :CarLights(3), PedLights(2) {
	CarLights.InsElem(car);
	PedLights.InsElem(ped);
}
char TLight::get(char place) {
	if (place == 'p') {
		if (PedLights.IsMember(0)) return 'r';
		else return 'g';
	}
	else {
		if (CarLights.IsMember(0)) return 'r';
		else if (PedLights.IsMember(1)) return 'g';
		else return 'y';
	}
	
}

void TLight::tick() {
	if (CarLights.IsMember(0)) { CarLights.DelElem(0); CarLights.InsElem(1); PedLights.DelElem(1); PedLights.InsElem(0); }
	else if (CarLights.IsMember(1)) { CarLights.DelElem(1); CarLights.InsElem(2); }
	else if (CarLights.IsMember(2)) { CarLights.DelElem(2); CarLights.InsElem(0); PedLights.DelElem(0); PedLights.InsElem(1); }
}