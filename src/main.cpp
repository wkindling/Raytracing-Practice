#include <fstream>
#include <sstream>
#include "ray.h"

using namespace std;

bool hit_sphere(const Vec3& center, float radius, const Ray& r)
{
	Vec3 ac = r.origin() - center;
	float a = r.direction().norm2();
	float b = 2.0*r.direction().dot(ac);
	float c = ac.norm2() - radius * radius;
	float delta = b * b - 4 * a*c;
	return (delta >= 0);
}

Vec3 color(const Ray& r)
{
	if (hit_sphere(Vec3(0, 0, -1), 0.5, r)) return Vec3(1, 0, 0);
	Vec3 direction = r.direction().unit();
	float t = 0.5*(direction.y() + 1.0);
	return (1 - t)*Vec3(1, 1, 1) + t * Vec3(0.5, 0.7, 1.0);
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
	for (int i = ny - 1; i >= 0; i--)
	{
		for (int j = 0; j < nx; j++)
		{
			float v = float(i) / float(ny);
			float u = float(j) / float(nx);
			Ray r(origin, lower_left + horizontal * u + vertical * v);
			Vec3 col = color(r);
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			os << ir << " " << ig << " " << ib << endl;
		}
	}
}