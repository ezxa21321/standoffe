#pragma once
#include "t_vec4.h"
#include "t_quaternion.h"

struct transformMatrix_t {
	vec4_t position;
	quaternion_t rotation;
	vec4_t scale;
};
