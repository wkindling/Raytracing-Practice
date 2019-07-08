#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include "hitable.h"

class Sphere : public Hitable
{
public:
	Sphere() {}
	Sphere(Vec3 cen, float r) :center(cen), radius(r) {}
	virtual ~Sphere() {}

	virtual bool hit(Ray& r, float t_min, float t_max, HitRecord& record);

public:
	Vec3 center;
	float radius;
};

//B^2 t^2 + 2B*(A-C)t+(A-C)^2-R^2=0
bool Sphere::hit(Ray& r, float t_min, float t_max, HitRecord& record)
{
	Vec3 ac = r.origin() - center;
	float a = r.direction().norm2();
	float b = 2 * r.direction().dot(ac);
	float c = ac.norm2() - radius * radius;
	float delta = b * b - 4 * a*c;
	if (delta > 0)
	{
		float temp = (-b - sqrt(delta)) / (2.0*a);
		if (temp <= t_max && temp >= t_min)
		{
			record.t = temp;
			record.position = r.locate_point(temp);
			record.normal = (record.position - center).unit();
			return true;
		}
		temp = (-b + sqrt(delta)) / (2.0*a);
		if (temp <= t_max && temp >= t_min)
		{
			record.t = temp;
			record.position = r.locate_point(temp);
			record.normal = (record.position - center).unit();
			return true;
		}
	}
	return false;
}

#endif