#pragma once
#include "Vector3.h"

struct AABB 
{
	Vector3 min; //!< 最小点
	Vector3 max; //!< 最大点

	static bool IsCollision(AABB aabb1, AABB aabb2);

};
