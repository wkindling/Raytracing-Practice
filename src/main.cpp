#include <fstream>
#include <sstream>
#include "sphere.h"
#include "hitablelist.h"

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
	os << "P3" << endl;
	os << nx << " " << ny << endl;
	os << "255" << endl;
	Vec3 lower_left(-2, -1, -1);
	Vec3 horizontal(4, 0, 0);
	Vec3 vertical(0, 2, 0);
	Vec3 origin(0, 0, 0);

	Hitable* object1 = new Sphere(Vec3(0, 0, -1), 0.5);
	Hitable* object2 = new Sphere(Vec3(0, -100.5, -1), 100);
	HitableList* world = new HitableList();
	world->add(object1);
	world->add(object2);
	
	for (int i = ny - 1; i >= 0; i--)
	{
		for (int j = 0; j < nx; j++)
		{
			float v = float(i) / float(ny);
			float u = float(j) / float(nx);
			Ray r(origin, lower_left + horizontal * u + vertical * v);
			Vec3 col = color(r, world);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			os << ir << " " << ig << " " << ib << endl;
		}
	}
}