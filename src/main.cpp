#include <fstream>
#include <sstream>
#include <random>
#include <ctime>

#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"

#define MAX_FLOAT 1e8

using namespace std;

Vec3 color(Ray& r, HitableList* world)
{
	HitRecord record;
	if (world->hit(r, 0, MAX_FLOAT, record))
	{
		return 0.5*Vec3(record.normal.x() + 1, record.normal.y() + 1, record.normal.z() + 1);
	}
	else
	{
		Vec3 direction = r.direction().unit();
		float t = 0.5*(direction.y() + 1);
		return (1 - t)*Vec3(1, 1, 1) + t * Vec3(0.5, 0.7, 1);
	}
}

int main()
{
	ofstream os("C:/Users/dell/Desktop/vec.ppm");

	int nx = 200;
	int ny = 100;
	int ns = 300;

	Hitable* object1 = new Sphere(Vec3(0, 0, -1), 0.5);
	Hitable* object2 = new Sphere(Vec3(0, -100.5, -1), 100);
	HitableList* world = new HitableList();
	world->add(object1);
	world->add(object2);

	Camera camera;

	default_random_engine e(time(0));
	uniform_real_distribution<double> ue(0, 1);

	os << "P3" << endl;
	os << nx << " " << ny << endl;
	os << "255" << endl;
	
	for (int i = ny - 1; i >= 0; i--)
	{
		for (int j = 0; j < nx; j++)
		{
			Vec3 col(0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(j+ue(e)) / float(nx);
				float v = float(i+ue(e)) / float(ny);
				Ray r = camera.shoot_ray(u, v);
				col += color(r, world);
			}
			col /= float(ns);

			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			os << ir << " " << ig << " " << ib << endl;
		}
	}
}