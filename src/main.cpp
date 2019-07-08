#include <fstream>
#include <sstream>
#include <random>
#include <ctime>

#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"

#define MAX_FLOAT 1e8

using namespace std;

default_random_engine e(time(0));
uniform_real_distribution<double> ue(0, 1);

Vec3 random_direction_in_sphere()
{
	Vec3 dir;
	do
	{
		dir = 2.0*Vec3(ue(e), ue(e), ue(e)) - Vec3(1, 1, 1);
	} while (dir.norm() >= 1.0);
	return dir;
}

Vec3 color(Ray& r, HitableList* world)
{
	HitRecord record;
	if (world->hit(r, 0.001, MAX_FLOAT, record))
	{
		Vec3 target = record.position + record.normal + random_direction_in_sphere();
		Ray ray(record.position, target - record.position); //reflection
		return 0.5*color(ray,world);
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
	cout << time(0) << endl;

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
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			os << ir << " " << ig << " " << ib << endl;
		}
	}
}