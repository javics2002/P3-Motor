#include "Entity.h"

namespace me {

	template<typename T, typename ...Ts>
	T* Entity::addComponent(Ts &&... args) {
		T* c = new T(std::forward<Ts>(args)...);
		c->setEntity(this);
		c->init();
		constexpr auto id = ec::cmpIdx<T>;

		if (cmpArray_[id] != nullptr) {
			removeComponent<T>();
		}

		cmpArray_[id] = c;
		components_.emplace_back(c);

		return c;
	}

	template<typename T>
	void Entity::removeComponent() {
		auto id = ec::cmpIdx<T>;
		if (cmpArray_[id] != nullptr) {
			Component* old_cmp = cmpArray_[id];
			cmpArray_[id] = nullptr;
			components_.erase( //
				std::find_if( //
					components_.begin(), //
					components_.end(), //
					[old_cmp](const Component* c) { //
				return c == old_cmp;
			}));
			delete old_cmp;
		}
	}

	template<typename T>
	inline T* Entity::getComponent() {
		auto id = ec::cmpIdx<T>;
		return static_cast<T*>(cmpArray_[id]);
	}

	template<typename T>
	inline bool Entity::hasComponent() {
		auto id = ec::cmpIdx<T>;
		return cmpArray_[id] != nullptr;
	}

	inline bool Entity::isActive() const {
		return active_;
	}

	inline void Entity::setActive(bool state) {
		active_ = state;
	}

	void Entity::update() {
		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			components_[i]->update();
		}
	}

	void Entity::lateUpdate() {
		std::size_t n = components_.size();
		for (auto i = 0u; i < n; i++) {
			components_[i]->lateUpdate();
		}
	}

};