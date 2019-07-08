#pragma once
#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <cassert>
#include <iostream>

class vec3
{
public:
	vec3() {}
	vec3(float v0, float v1, float v2) { v[0] = v0; v[1] = v1; v[2] = v2; }
	vec3(float t) { v[0] = t; v[1] = t; v[2] = t; }

	inline float x() const { return v[0]; }
	inline float y() const { return v[1]; }
	inline float z() const { return v[2]; }

	inline float r() const { return v[0]; }
	inline float g() const { return v[1]; }
	inline float b() const { return v[2]; }

	inline const vec3 operator+() const { return *this; }
	inline const vec3 operator-() const { return vec3(-v[0], -v[1], -v[2]); }
	inline float operator[](int index) const { assert(index >= 0 && index <= 2); return v[index]; }
	inline float& operator[](int index) { assert(index >= 0 && index <= 2); return v[index]; }

	inline vec3& operator+=(const vec3& v2) { v[0] += v2[0]; v[1] += v2[1]; v[2] += v2[2]; return *this; }
	inline vec3& operator-=(const vec3& v2) { v[0] -= v2[0]; v[1] -= v2[1]; v[2] -= v2[2]; return *this; }
	inline vec3& operator*=(const vec3& v2) { v[0] *= v2[0]; v[1] *= v2[1]; v[2] *= v2[2]; return *this; }
	inline vec3& operator/=(const vec3& v2) { v[0] /= v2[0]; v[1] /= v2[1]; v[2] /= v2[2]; return *this; }
	inline vec3& operator*=(const float t) { v[0] *= t; v[1] *= t; v[2] *= t; return *this; }
	inline vec3& operator/=(const float t) { v[0] /= t; v[1] /= t; v[2] /= t; return *this; }

	inline vec3 operator+(const vec3& v2) { return vec3(v[0] + v2[0], v[1] + v2[1], v[2] + v2[2]); }
	inline vec3 operator-(const vec3& v2) { return vec3(v[0] - v2[0], v[1] - v2[1], v[2] - v2[2]); }
	inline vec3 operator*(const vec3& v2) { return vec3(v[0] * v2[0], v[1] * v2[1], v[2] * v2[2]); }
	inline vec3 operator/(const vec3& v2) { return vec3(v[0] / v2[0], v[1] / v2[1], v[2] / v2[2]); }
	inline vec3 operator*(const float t) { return vec3(v[0] * t, v[1] * t, v[2] * t); }
	inline vec3 operator/(const float t) { return vec3(v[0] / t, v[1] / t, v[2] / t); }
	
	inline float dot(const vec3& v2) { return v[0] * v2[0] + v[1] * v2[1] + v[2] * v2[2]; }
	inline vec3 cross(const vec3& v2){ return vec3(v[1] * v2[2] - v[2] * v2[1], -v[0] * v2[2] + v[2] * v2[0], v[0] * v2[1] - v[1] * v2[0]); }
	
	inline float norm2() const { return v[0] * v[0] + v[1] * v[1] + v[2] * v[2]; }
	inline float norm() const { return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]); }
	inline void normalize() { float n = this->norm(); v[0] /= n; v[1] /= n; v[2] /= n; }
	inline vec3& unit() { float n = this->norm(); v[0] /= n; v[1] /= n; v[2] /= n; return *this; }

	friend std::istream& operator>>(std::istream& is, vec3& t);
	friend std::ostream& operator<<(std::ostream& os, const vec3& t);

private:
	float v[3];
};

inline std::istream& operator>>(std::istream& is, vec3& t)
{
	is >> t[0] >> t[1] >> t[2];
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& t)
{
	os << t[0] << " " << t[1] << " " << t[2];
	return os;
}


#endif