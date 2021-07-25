#include "Collision.h"

void Collision::getpoly(polygon &poly, std::fstream &file) {
	if (file) {
		float temp{};
		float temp2{};
		file >> poly.pos.x >> poly.pos.y >> poly.angle >> temp >> temp2;
		for (int i{ 0 }; i < 3; i++) {
			poly.o.push_back({ temp, temp2 });
			file >> temp >> temp2;
		}
		poly.o.push_back({ temp, temp2 });
		poly.p.resize(4);
	}
	else { std::cout<< "File failed to open"; }
}

void Collision::updatepoly(polygon& quad, int camx, int camy, float scale) {
	for (int i = 0; i < quad.o.size(); i++) {
		quad.p[i] = {
			((quad.o[i].x * cosf(quad.angle)) - (quad.o[i].y * sinf(quad.angle)) + quad.pos.x) * scale + camx,
			((quad.o[i].x * sinf(quad.angle)) + (quad.o[i].y * cosf(quad.angle)) + quad.pos.y) * scale + camy
		};
		quad.overlap = false;
	}
}

bool Collision::collision(polygon& r1, polygon& r2) {

	polygon* poly1 = &r1;
	polygon* poly2 = &r2;

	float overlap = INFINITY;

	for (int i{ 0 }; i < 2; i++) {

		if (i == 1) {
			poly1 = &r2;
			poly2 = &r1;
		}

		for (int i = 0; i < poly1->p.size(); i++) {
			int j = (i + 1) % poly1->p.size();
			olc::vf2d axisProj = { -(poly1->p[j].y - poly1->p[i].y), poly1->p[j].x - poly1->p[i].x };

			float min_r1 = INFINITY, max_r1 = -INFINITY;
			for (int i = 0; i < poly1->p.size(); i++) {
				float q = (poly1->p[i].x * axisProj.x + poly1->p[i].y * axisProj.y);
				min_r1 = std::min(min_r1, q);
				max_r1 = std::max(max_r1, q);
			}

			float min_r2 = INFINITY, max_r2 = -INFINITY;
			for (int i = 0; i < poly2->p.size(); i++)
			{
				float q = (poly2->p[i].x * axisProj.x + poly2->p[i].y * axisProj.y);
				min_r2 = std::min(min_r2, q);
				max_r2 = std::max(max_r2, q);
			}

			overlap = std::min(std::min(max_r1, max_r2) - std::max(min_r1, min_r2), overlap);

			if (!(max_r2 >= min_r1 && max_r1 >= min_r2))
				return false;
		}
	}
	return true;
}

void Collision::allCollision(std::vector<polygon*> f1, std::vector<polygon*> f2){
	for (int i = 0; i < f1.size(); i++) {
		for (int j = i + 1; j < f2.size(); j++) {
			f1[j]->overlap = Collision::collision(*f1[j], *f2[i]);
			if (f1[j]->overlap) {
				f2[i]->overlap = true;
				break;
			}
		}
	}
}

void Collision::drawpoly(polygon poly) {
	for (int i = 0; i < poly.p.size(); i++) {
		olc::Renderer::ptrPGE->DrawLine(poly.p[i].x, poly.p[i].y, poly.p[(i + 1) % poly.p.size()].x, poly.p[(i + 1) % poly.p.size()].y, (poly.overlap ? olc::RED : olc::WHITE));
	}
}