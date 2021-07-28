#include "Fighter.h"

void Fighter::linkFilesOne(std::vector<polygon*> hitBoxes) {
	
	std::fstream center{ "Hitboxes//1center.txt" };
	std::fstream sword{ "Hitboxes//1sword.txt" };

	Collision::getpoly(*hitBoxes[0], center);
	Collision::getpoly(*hitBoxes[1], sword);
}

void Fighter::linkFilesTwo(std::vector<polygon*> hitBoxes) {

	std::fstream center{ "Hitboxes//2center.txt" };
	std::fstream sword{ "Hitboxes//2sword.txt" };

	Collision::getpoly(*hitBoxes[0], center);
	Collision::getpoly(*hitBoxes[1], sword);
}

