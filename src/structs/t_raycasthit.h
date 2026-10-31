#pragma once
#include "t_vec3.h"
#include "t_vec2.h"

struct raycasthit_t {
	vec3_t m_Point{};
	vec3_t m_Normal{};
	unsigned int m_FaceID{};
	float m_Distance{};
	vec2_t m_UV{};
	int m_Collider{};
	void *get_collider() const;
};
