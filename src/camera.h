#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <random>
#include <ctime>
#include "ray.h"

class Camera
{
public:
	Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist)
	{
		lens_radius = aperture / 2.0; //lens
		float theta = vfov * 3.1415926535 / 180; //turn to radius
		float half_height = tan(theta / 2.0); 
		float half_width = half_height * aspect;
		origin = lookfrom;

		forward = (lookat - lookfrom).unit();
		right = (forward.cross(vup)).unit();
		up = (right.cross(forward));

		lower_left = origin - half_height * focus_dist*up - half_width * focus_dist*right + focus_dist * forward;
		horizontal = 2 * half_width*focus_dist*right;
		vertical = 2 * half_height*focus_dist*up;
	}

	Vec3 random_sample_lens() // random sample in the circle lens
	{		
		Vec3 sample;
		do
		{
			sample = 2 * Vec3((float)rand()/RAND_MAX, (float)rand() / RAND_MAX, 0) - Vec3(1, 1, 0);
		} while (sample.norm2() >= 1.0);
		return sample;
	}
	
	Ray shoot_ray(float s, float t)
	{
		Vec3 sample = random_sample_lens()*lens_radius;
		Vec3 offset = sample.x()*right + sample.y()*up;
		return Ray(origin + offset, lower_left + s * horizontal + t * vertical - origin - offset);
	}



public:
	Vec3 origin;
	Vec3 lower_left;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 forward, right, up;
	float lens_radius;
};

#endif