#include "Collision.h"

void Collision::makequad(polygon &quad) {
	quad.pos = { 100,100 };
	quad.angle = { 0.0f };
	quad.o.push_back({ -30,-30 });
	quad.o.push_back({ -30,30 });
	quad.o.push_back({ 30,30 });
	quad.o.push_back({ 30,-30 });
	quad.p.resize(4);
}