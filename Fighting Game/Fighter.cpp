#include "Fighter.h"

void Fighter::linkFiles(std::vector<polygon*> hitBoxes, Fighter fighter) {
	std::fstream center{ "Hitboxes//center.txt" };
	std::fstream head{ "Hitboxes//head.txt" };
	std::fstream lArm{ "Hitboxes//lArm.txt" };
	std::fstream lLeg{ "Hitboxes//lLeg.txt" };
	std::fstream rArm{ "Hitboxes//rArm.txt" };
	std::fstream rLeg{ "Hitboxes//Leg.txt" };
	Collision::getpoly(*fighter.hitBoxes[0], center);
	Collision::getpoly(*fighter.hitBoxes[1], head);
	Collision::getpoly(*fighter.hitBoxes[2], lArm);
	Collision::getpoly(*fighter.hitBoxes[3], lLeg);
	Collision::getpoly(*fighter.hitBoxes[4], rArm);
	Collision::getpoly(*fighter.hitBoxes[5], rLeg);
}
