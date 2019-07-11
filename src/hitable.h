#pragma once
#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

class Material;

struct HitRecord
{
	float t;		//ray parameter
	Vec3 position;  //hit position
	Vec3 normal;	//hit normal
	Material *mat;  //hit material
};

class Hitable
{
public:
	virtual bool hit(Ray& r, float t_min, float t_max, HitRecord& record)=0; //pure virtual function
};

#endif