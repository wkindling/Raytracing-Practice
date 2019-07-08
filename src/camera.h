#pragma once
#ifndef CAMERA
#define CAMERA

#include "ray.h"

class Camera
{
public:
	Camera(Vec3 _lower_left = Vec3(-2, -1, -1), Vec3 _horizontal = Vec3(4, 0, 0), Vec3 _vertical = Vec3(0, 2, 0), Vec3 _ori = Vec3(0, 0, 0))
	{
		ori = _ori;
		lower_left = _lower_left;
		horizontal = _horizontal;
		vertical = _vertical;
	}
	virtual ~Camera() {}
	Ray shoot_ray(float u, float v)
	{
		return Ray(ori, lower_left + u * horizontal + v * vertical - ori);
	}

public:
	Vec3 ori;
	Vec3 lower_left;
	Vec3 horizontal;
	Vec3 vertical;



};


#endif