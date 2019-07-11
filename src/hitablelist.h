#pragma once
#ifndef HITABLELIST_H
#define HITABLELIST_H

#include <vector>
#include "hitable.h"

class HitableList :public Hitable
{
public:
	HitableList() {}
	virtual bool hit(Ray& r, float t_min, float t_max, HitRecord& record);
	virtual ~HitableList() {}
	
	void add(Hitable* hit);

public:
	std::vector<Hitable*> list;
};

bool HitableList::hit(Ray& r, float t_min, float t_max, HitRecord& record)
{
	HitRecord temp;
	bool hit_anything = false;
	float closet_so_far = t_max;
	//TODO: prune + GPU parallel
	for (int i = 0; i < list.size(); i++) //Find the closet hit point 
	{
		if (list[i]->hit(r, t_min, closet_so_far, temp))
		{
			hit_anything = true;
			closet_so_far = temp.t;
			record = temp;
		}
	}
	return hit_anything;
}

void HitableList::add(Hitable* hit)
{
	list.push_back(hit);
}

#endif