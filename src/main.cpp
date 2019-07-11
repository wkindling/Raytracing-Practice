#include <fstream>
#include <sstream>
#include <random>
#include <ctime>

#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"
#include "material.h"

#define MAX_FLOAT 1e8

using namespace std;

Vec3 color(Ray& r, HitableList* world, int depth)
{
	HitRecord record;
	if (world->hit(r, 0.001, MAX_FLOAT, record))
	{
		Ray scattered;
		Vec3 attenuation;
		if (depth < 50 && record.mat->scatter(r, record, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return Vec3(0, 0, 0);
		}
	}
	else
	{
		Vec3 unit_direction = r.direction().unit();
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1 - t)*Vec3(1, 1, 1) + t * Vec3(0.3, 0.6, 0.9);
	}
}

HitableList* random_scene()
{
	int n = 500;
	HitableList* world = new HitableList();

	Hitable* big_sphere = new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3(0.3, 0.9, 0.6)));
	world->add(big_sphere);
	int i = 1;

#pragma omp parallel for
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = (float)rand()/RAND_MAX;
			Vec3 center(a + 0.9*(float)rand()/RAND_MAX, 0.2, b+0.8*(float)rand()/RAND_MAX);
			if ((center - Vec3(4, 0.2, 0)).norm() > 0.9)
			{
				if (choose_mat < 0.8)
				{
					Hitable* diffuse_ball = new Sphere(center, 0.2, new Lambertian(Vec3(((float)rand()/RAND_MAX)*((float)rand()/RAND_MAX), ((float)rand()/RAND_MAX)*((float)rand()/RAND_MAX), ((float)rand()/RAND_MAX)*((float)rand()/RAND_MAX))));
					world->add(diffuse_ball);
				}
				else if (choose_mat < 0.95)
				{
					Hitable* metal_ball = new Sphere(center, 0.2, new Metal(Vec3(0.5*(1 + (float)rand()/RAND_MAX), 0.5*(1 + (float)rand()/RAND_MAX), 0.5*(1 + (float)rand()/RAND_MAX)), 0.5*(float)rand()/RAND_MAX));
					world->add(metal_ball);
				}
				else
				{
					Hitable* glass_ball = new Sphere(center, 0.2, new Dielectric(1.5));
				}
			}
		}
	}
	Hitable* glass_ball = new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5));
	Hitable* diffuse_ball = new Sphere(Vec3(-4, 1, 0), 1, new Lambertian(Vec3(1.0, 0.6, 0.4)));
	Hitable* metal_ball = new Sphere(Vec3(4, 1, 0), 1, new Metal(Vec3(0.8, 0.3, 0.3), 0));
	world->add(glass_ball);
	world->add(diffuse_ball);
	world->add(metal_ball);
	return world;
}


int main()
{
	srand(time(NULL));
	ofstream os("C:/Users/dell/Desktop/vec.ppm");

	int nx = 1920;
	int ny = 1080;
	int ns = 100;

	os << "P3" << endl;
	os << nx << " " << ny << endl;
	os << "255" << endl;

	HitableList* world = random_scene();

	Vec3 lookfrom(13, 2, 3);
	Vec3 lookat(0, 0, 0);
	float dist_to_focus = 10.0;
	float aperture = 0.1;

	Camera camera(lookfrom, lookat, Vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);

	for (int i = ny - 1; i >= 0; i--)
	{
		for (int j = 0; j < nx; j++)
		{
			Vec3 col(0);
			for (int s = 0; s < ns; s++)
			{
				float u = float(j+(float)rand()/RAND_MAX) / float(nx);
				float v = float(i+(float)rand()/RAND_MAX) / float(ny);
				Ray r = camera.shoot_ray(u, v);
				col += color(r, world, 0);
			}
			col /= float(ns);
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			os << ir << " " << ig << " " << ib << endl;
		}
		cout << 100-(float)i / ny * 100 << "%" << endl;
	}
}