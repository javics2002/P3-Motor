/**
The main function of this class is to be the wrapper 
of a set of components.
*/

#pragma once
#ifndef __EC_ENTITY
#define __EC_ENTITY

#include <algorithm>
#include <array>
#include <bitset>
#include <vector>
#include <iostream>
#include "Component.h"
#include "ec.h"


namespace me {

	class Scene;

	class Entity {
		friend Scene;

	public:

		/**
		Build the foundation of the entity.
		*/
		Entity(Scene* scn);

		/**
		Delete all the components added to the entity.
		*/
		virtual ~Entity();

		/**
		Add a new component. If the component
		already exists, this will replace them.
		@return Reference to the new component.
		*/
		template<typename T, typename ...Ts>
		T* addComponent(Ts &&... args);

		/**
		Remove completely a component.
		*/
		template<typename T>
		void removeComponent();

		/**
		Get the reference a suggested component.
		@return Reference to the component.
		*/
		template<typename T>
		inline T* getComponent();

		/**
		Check if the component has already been added.
		@return Boolean confirmation.
		*/
		template<typename T>
		inline bool hasComponent();

		/**
		Set the associated scene for the entity.
		*/
		inline void setScene(Scene* scn);

		/**
		Get the associated scene of the entity.
		*/
		inline Scene* getScene();

		/**
		Check if the entity is active.
		@return Boolean confirmation.
		*/
		inline bool isActive() const;

		/**
		Set the entity activity to the boolean petition.
		*/
		inline void setActive(bool state);

		/**
		Run all the added components update method.
		*/
		void update();

		/**
		Run all the added components lateUpdate method.
		*/
		void lateUpdate();

	private:

		bool active_;
		Scene* scn_;
		std::vector<Component*> components_;
		std::array<Component*, ec::maxComponent> cmpArray_;

	};

};

#endif