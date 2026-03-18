#include "Input.h"

#include "ServiceProvider/ServiceProvider.h"

namespace WaveEngine
{
	Input::Input()
	{
	}

	Input::~Input()
	{
	}

	int Input::GetGlfwKeyFromKey(Keys key)
	{
		switch (key)
		{
		case Keys::A: return GLFW_KEY_A;
		case Keys::B: return GLFW_KEY_B;
		case Keys::C: return GLFW_KEY_C;
		case Keys::D: return GLFW_KEY_D;
		case Keys::E: return GLFW_KEY_E;
		case Keys::F: return GLFW_KEY_F;
		case Keys::G: return GLFW_KEY_G;
		case Keys::H: return GLFW_KEY_H;
		case Keys::I: return GLFW_KEY_I;
		case Keys::J: return GLFW_KEY_J;
		case Keys::K: return GLFW_KEY_K;
		case Keys::L: return GLFW_KEY_L;
		case Keys::M: return GLFW_KEY_M;
		case Keys::N: return GLFW_KEY_N;
		case Keys::O: return GLFW_KEY_O;
		case Keys::P: return GLFW_KEY_P;
		case Keys::Q: return GLFW_KEY_Q;
		case Keys::R: return GLFW_KEY_R;
		case Keys::S: return GLFW_KEY_S;
		case Keys::T: return GLFW_KEY_T;
		case Keys::U: return GLFW_KEY_U;
		case Keys::V: return GLFW_KEY_V;
		case Keys::W: return GLFW_KEY_W;
		case Keys::X: return GLFW_KEY_X;
		case Keys::Y: return GLFW_KEY_Y;
		case Keys::Z: return GLFW_KEY_Z;
		case Keys::ZERO: return GLFW_KEY_0;
		case Keys::ONE: return GLFW_KEY_1;
		case Keys::TWO: return GLFW_KEY_2;
		case Keys::THREE: return GLFW_KEY_3;
		case Keys::FOUR: return GLFW_KEY_4;
		case Keys::FIVE: return GLFW_KEY_5;
		case Keys::SIX: return GLFW_KEY_6;
		case Keys::SEVEN: return GLFW_KEY_7;
		case Keys::EIGHT: return GLFW_KEY_8;
		case Keys::NINE: return GLFW_KEY_9;
		case Keys::UP: return GLFW_KEY_UP;
		case Keys::DOWN: return GLFW_KEY_DOWN;
		case Keys::RIGHT: return GLFW_KEY_RIGHT;
		case Keys::LEFT: return GLFW_KEY_LEFT;
		case Keys::SPACE: return GLFW_KEY_SPACE;
		case Keys::APOSTROPHE: return GLFW_KEY_APOSTROPHE;
		case Keys::COMMA: return GLFW_KEY_COMMA;
		case Keys::MINUS: return GLFW_KEY_MINUS;
		case Keys::PERIOD: return GLFW_KEY_PERIOD;
		case Keys::SLASH: return GLFW_KEY_SLASH;
		case Keys::SEMICOLON: return GLFW_KEY_SEMICOLON;
		case Keys::EQUAL: return GLFW_KEY_EQUAL;
		case Keys::LEFT_BRACKET: return GLFW_KEY_LEFT_BRACKET;
		case Keys::RIGHT_BRACKET: return GLFW_KEY_RIGHT_BRACKET;
		case Keys::BACKSLASH: return GLFW_KEY_BACKSLASH;
		case Keys::GRAVE_ACCENT: return GLFW_KEY_GRAVE_ACCENT;
		case Keys::ESCAPE: return GLFW_KEY_ESCAPE;
		case Keys::ENTER: return GLFW_KEY_ENTER;
		case Keys::TAB: return GLFW_KEY_TAB;
		case Keys::BACKSPACE: return GLFW_KEY_BACKSPACE;
		case Keys::INSERT: return GLFW_KEY_INSERT;
		case Keys::DELETE: return GLFW_KEY_DELETE;
		case Keys::PAGE_DOWN: return GLFW_KEY_PAGE_DOWN;
		case Keys::PAGE_UP: return GLFW_KEY_PAGE_UP;
		case Keys::HOME: return GLFW_KEY_HOME;
		case Keys::END: return GLFW_KEY_END;
		case Keys::CAPS_LOCK: return GLFW_KEY_CAPS_LOCK;
		case Keys::SCROLL_LOCK: return GLFW_KEY_SCROLL_LOCK;
		case Keys::NUM_LOCK: return GLFW_KEY_NUM_LOCK;
		case Keys::PRINT_SCREEN: return GLFW_KEY_PRINT_SCREEN;
		case Keys::PAUSE: return GLFW_KEY_PAUSE;
		case Keys::F1: return GLFW_KEY_F1;
		case Keys::F2: return GLFW_KEY_F2;
		case Keys::F3: return GLFW_KEY_F3;
		case Keys::F4: return GLFW_KEY_F4;
		case Keys::F5: return GLFW_KEY_F5;
		case Keys::F6: return GLFW_KEY_F6;
		case Keys::F7: return GLFW_KEY_F7;
		case Keys::F8: return GLFW_KEY_F8;
		case Keys::F9: return GLFW_KEY_F9;
		case Keys::F10: return GLFW_KEY_F10;
		case Keys::F11: return GLFW_KEY_F11;
		case Keys::F12: return GLFW_KEY_F12;
		case Keys::F13: return GLFW_KEY_F13;
		case Keys::F14: return GLFW_KEY_F14;
		case Keys::F15: return GLFW_KEY_F15;
		case Keys::F16: return GLFW_KEY_F16;
		case Keys::F17: return GLFW_KEY_F17;
		case Keys::F18: return GLFW_KEY_F18;
		case Keys::F19: return GLFW_KEY_F19;
		case Keys::F20: return GLFW_KEY_F20;
		case Keys::F21: return GLFW_KEY_F21;
		case Keys::F22: return GLFW_KEY_F22;
		case Keys::F23: return GLFW_KEY_F23;
		case Keys::F24: return GLFW_KEY_F24;
		case Keys::F25: return GLFW_KEY_F25;
		case Keys::KP_1: return GLFW_KEY_KP_1;
		case Keys::KP_2: return GLFW_KEY_KP_2;
		case Keys::KP_3: return GLFW_KEY_KP_3;
		case Keys::KP_4: return GLFW_KEY_KP_4;
		case Keys::KP_5: return GLFW_KEY_KP_5;
		case Keys::KP_6: return GLFW_KEY_KP_6;
		case Keys::KP_7: return GLFW_KEY_KP_7;
		case Keys::KP_8: return GLFW_KEY_KP_8;
		case Keys::KP_9: return GLFW_KEY_KP_9;
		case Keys::KP_DECIMAL: return GLFW_KEY_KP_DECIMAL;
		case Keys::KP_DIVIDE: return GLFW_KEY_KP_DIVIDE;
		case Keys::KP_MULTIPLY: return GLFW_KEY_KP_MULTIPLY;
		case Keys::KP_SUBTRACT: return GLFW_KEY_KP_SUBTRACT;
		case Keys::KP_ADD: return GLFW_KEY_KP_ADD;
		case Keys::KP_ENTER: return GLFW_KEY_KP_ENTER;
		case Keys::KP_EQUAL: return GLFW_KEY_KP_EQUAL;
		case Keys::LEFT_SHIFT: return GLFW_KEY_LEFT_SHIFT;
		case Keys::LEFT_CONTROL: return GLFW_KEY_LEFT_CONTROL;
		case Keys::LEFT_ALT: return GLFW_KEY_LEFT_ALT;
		case Keys::LEFT_SUPER: return GLFW_KEY_LEFT_SUPER;
		case Keys::RIGHT_SHIFT: return GLFW_KEY_RIGHT_SHIFT;
		case Keys::RIGHT_CONTROL: return GLFW_KEY_RIGHT_CONTROL;
		case Keys::RIGHT_ALT: return GLFW_KEY_RIGHT_ALT;
		case Keys::RIGHT_SUPER: return GLFW_KEY_RIGHT_SUPER;
		default: return -1;
		}
	}

	Window* Input::GetWindow()
	{
		return ServiceProvider::Instance().Get<Window>();
	}

	bool Input::IsKeyPressed(Keys key)
	{
		int keyToUse = GetGlfwKeyFromKey(key);

		return glfwGetKey(GetWindow()->GetGLFWindow(), keyToUse) == GLFW_PRESS ||
			glfwGetKey(GetWindow()->GetGLFWindow(), keyToUse) == GLFW_REPEAT;
	}
}
