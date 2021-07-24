#include "Fighter.h"

void Fighter::linkFiles(std::vector<polygon*> hitBoxes) {
	std::fstream center{ "Hitboxes//center.txt" };
	std::fstream head{ "Hitboxes//head.txt" };
	std::fstream lArm{ "Hitboxes//lArm.txt" };
	std::fstream lLeg{ "Hitboxes//lLeg.txt" };
	std::fstream rArm{ "Hitboxes//rArm.txt" };
	std::fstream rLeg{ "Hitboxes//Leg.txt" };
	Collision::getpoly(*hitBoxes[0], center);
	Collision::getpoly(*hitBoxes[1], head);
	Collision::getpoly(*hitBoxes[2], lArm);
	Collision::getpoly(*hitBoxes[3], lLeg);
	Collision::getpoly(*hitBoxes[4], rArm);
	Collision::getpoly(*hitBoxes[5], rLeg);
}
