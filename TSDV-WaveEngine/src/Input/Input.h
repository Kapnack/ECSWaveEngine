#pragma once

#include "Export.h"
#include "Window/Window.h"
#include "ServiceProvider/Service.h"
#include "WaveMath/Vector2/Vector2.h"

namespace WaveEngine
{
	class Engine;

	enum class WAVEEXPORT Keys
	{
		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		ZERO,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		UP,
		DOWN,
		RIGHT,
		LEFT,
		SPACE,
		APOSTROPHE,
		COMMA,
		MINUS,
		PERIOD,
		SLASH,
		SEMICOLON,
		EQUAL,
		LEFT_BRACKET,
		RIGHT_BRACKET,
		BACKSLASH,
		GRAVE_ACCENT,
		ESCAPE,
		ENTER,
		TAB,
		BACKSPACE,
		INSERT,
		DELETE,
		PAGE_DOWN,
		PAGE_UP,
		HOME,
		END,
		CAPS_LOCK,
		SCROLL_LOCK,
		NUM_LOCK,
		PRINT_SCREEN,
		PAUSE,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		F13,
		F14,
		F15,
		F16,
		F17,
		F18,
		F19,
		F20,
		F21,
		F22,
		F23,
		F24,
		F25,
		KP_1,
		KP_2,
		KP_3,
		KP_4,
		KP_5,
		KP_6,
		KP_7,
		KP_8,
		KP_9,
		KP_DECIMAL,
		KP_DIVIDE,
		KP_MULTIPLY,
		KP_SUBTRACT,
		KP_ADD,
		KP_ENTER,
		KP_EQUAL,
		LEFT_SHIFT,
		LEFT_CONTROL,
		LEFT_ALT,
		LEFT_SUPER,
		RIGHT_SHIFT,
		RIGHT_CONTROL,
		RIGHT_ALT,
		RIGHT_SUPER
	};

	class WAVEEXPORT Input : public Service
	{
	private:

		Vector2 previousMousePosition;
		Vector2 currentMousePosition;
		Vector2 mouseDirection;

		bool lockedMouse = false;

		int GetGlfwKeyFromKey(Keys key) const;

		Window* GetWindow() const;

		void Update();

		friend class Engine;

	public:

		static Input& Get();

		Input();
		~Input();

		Vector2 GetMousePosition() const;
		Vector2 GetMouseDirection() const;
		bool IsKeyPressed(Keys key) const;

		void SetCursorLocked(bool locked);
	};
}