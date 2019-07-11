#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H

#include <random>
#include <ctime>

#include "ray.h"
#include "hitable.h"

class Material
{
public:
	virtual bool scatter(Ray& in, HitRecord& record, Vec3& attenuation, Ray& scattered) = 0;
	Vec3 random_direction_in_sphere()
	{
		Vec3 dir;
		do
		{
			dir = 2.0*Vec3((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX) - Vec3(1, 1, 1);
		} while (dir.norm2() >= 1.0);
		return dir;
	}
};

class Lambertian : public Material
{
public:
	Lambertian(Vec3 al): albedo(al) {}
	virtual ~Lambertian() {}

	virtual bool scatter(Ray& in, HitRecord& record, Vec3& attenuation, Ray& scattered)
	{
		Vec3 target = record.position + record.normal + random_direction_in_sphere(); // scatter randomly
		scattered = Ray(record.position, target - record.position);
		attenuation = albedo;
		return true;
	}
public:
	Vec3 albedo;
};

class Metal :public Material
{
public:
	Metal(Vec3 al, float f) :albedo(al) { if (f < 1) fuzz = f; else fuzz = 1; }
	virtual ~Metal() {}

	virtual bool scatter(Ray& in, HitRecord& record, Vec3& attenuation, Ray& scattered)
	{
		Vec3 reflected = in.direction().unit().reflect(record.normal);
		scattered = Ray(record.position, reflected+fuzz*random_direction_in_sphere());
		attenuation = albedo;
		return (scattered.direction().dot(record.normal) > 0);
	}
public:
	Vec3 albedo;
	float fuzz;
};

class Dielectric : public Material
{
public:
	Dielectric(float ref) : nmat_over_nair(ref) {}
	virtual ~Dielectric() {}

	float schlick(float cosi, float n21)
	{
		float r0 = (1 - n21) / (1 + n21);
		r0 = r0 * r0;
		return r0 + (1 - r0)*pow((1 - cosi), 5);
	}

	virtual bool scatter(Ray& in, HitRecord& record, Vec3& attenuation, Ray& scattered)
	{
		Vec3 outward_normal;
		Vec3 reflected = in.direction().reflect(record.normal);
		float n12;
		attenuation = Vec3(1, 1, 1);
		Vec3 refracted;
		float reflect_prob;
		float cosine;

		if (in.direction().dot(record.normal) > 0) // from dielectric into air
		{
			outward_normal = -record.normal;
			n12 = nmat_over_nair;
			cosine = in.direction().dot(record.normal) / in.direction().norm();
			cosine = sqrt(1 - n12 * n12*(1 - cosine * cosine)); // the angle in air
		}
		else //from air into dielectric
		{
			outward_normal = record.normal;
			n12 = 1.0 / nmat_over_nair;
			cosine = -in.direction().dot(record.normal) / in.direction().norm(); // the angle in air
		}
		
		if (in.direction().refract(outward_normal, n12, refracted))
		{
			reflect_prob = schlick(cosine, nmat_over_nair); // air to dielectric
		}
		else reflect_prob = 1;

		if ((float)rand()/RAND_MAX < reflect_prob)
		{
			scattered = Ray(record.position, reflected);
		}
		else
		{
			scattered = Ray(record.position, refracted);
		}
		return true;
	}

public:
	float nmat_over_nair;
};


#endif