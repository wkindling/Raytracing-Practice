#pragma once
#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
public:
	Ray() {}
	Ray(const Vec3 origin, const Vec3 direction) { ori = origin; dir = direction; }
	virtual ~Ray() {}

	Vec3 origin() const { return ori; }
	Vec3 direction() const { return dir; }

	Vec3 locate_point(float t) { return ori + dir * t; }

private:
	Vec3 ori;
	Vec3 dir;
};



#endif