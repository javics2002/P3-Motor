#pragma once
#ifndef __EC_COLLIDER
#define __EC_COLLIDER

#include "Utils/Vector3.h"
#include "Component.h"
#include "Entity.h"

namespace me{


	class Collider : public Component
	{
	public:
		Collider();
		virtual ~Collider();


		/**
		Set the entity activity to the boolean petition.
		@param Boolean state activity.
		*/
		virtual void onCollisionEnter(Entity* other);

		/**
		Set the entity activity to the boolean petition.
		@param Boolean state activity.
		*/
		virtual void onCollisionStay(Entity* other);


		/**
		Set the entity activity to the boolean petition.
		@param Boolean state activity.
		*/
		virtual void onCollisionExit(Entity* other);

	};
}

#endif 


