/**
 * @file	Collisions2D.h
 * @brief   �й���ײ���㺯������
 * @author	Arty
 **/


#pragma once
#include "Core/Struct.h"

class Collider;

namespace Physics2D
{
	class Collisions2D final
	{
	public:
		static bool CollisionTestCircleToCircle(Collider* c1, Collider* c2, FHitResult& hitResult);

		static bool CollisionTestPolygonToPolygon(Collider* c1, Collider* c2, FHitResult& hitResult);
	};
}