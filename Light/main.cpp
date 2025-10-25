#include "Light.h"
#include "tbitfield.h"
int main() {
	TLight cross(Crypter('r'), Crypter('g'));
	int a;
	while (1) {
		std::cout << "ped: " << cross.get('p') << "\ncar: " << cross.get('c');
		std:cin >> a;
		if (a == 0) break;
		cross.tick();
	}
}