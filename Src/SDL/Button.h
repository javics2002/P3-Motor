#pragma once
#ifndef __SDL_BUTTON
#define __SDL_BUTTON

#include <string>
#include <unordered_map>
#include <SDL3/SDL_events.h>

namespace me {
	/**
	Representation of a virtual button, so you can unify input
	given any controller, keyboard or mouse.
	*/
	struct Button {
		//Value
		bool pressed;
	};

	//Represents a physical button or key that can trigger a virtual button.
	struct Input {
		/*
		SDL_EVENT_KEY_DOWN for keyboard key presses
		SDL_MouseButtonEvent for mouse clicks
		SDL_ControllerButtonEvent for controller presses
		*/
		SDL_EventType type;

		/*Which key, mouse button, or controller button has been pressed.
		Represents a value of SDL_KeyCode, SDL_BUTTON or SDL_GamepadButton depending on the type of the event.*/
		int which;

		bool operator==(const Input& i) const
		{
			return type == i.type && which == i.which;
		}
	};

	//Provides hash suppport for using struct Input as a key in std::unordered_map.
	struct InputHasher {
		size_t operator()(const Input& t) const {
			return std::hash<int>()(t.which) ^ std::hash<int>()(t.type);
		}
	};

	/*
	Stores data for virtual buttons' callbacks.
	*/
	struct OnButtonPressedInfo {
		//Simple callback provided by the user.
		int(*callback)(void*); 

		//Additional userdata given to callback as a parameter.
		void* additionalData;

		//Filtered callback that calls callback if the event source matches any of the virtual button's bindings.
		SDL_EventFilter filter;

		//Reference to InputManager's mButtonBindings multimap.
		std::unordered_multimap<Input, std::string, InputHasher>* buttonBindings; 

		//Name of the button this callback belongs to.
		std::string buttonName;
	};
}

#endif