#pragma once

#include <Unified-Engine/includeGL.h>

namespace UnifiedEngine
{
    enum KeyboardButtonEnums{
        //Numbers
		Key_0 = GLFW_KEY_0,
		Key_1 = GLFW_KEY_1,
		Key_2 = GLFW_KEY_2,
		Key_3 = GLFW_KEY_3,
		Key_4 = GLFW_KEY_4,
		Key_5 = GLFW_KEY_5,
		Key_6 = GLFW_KEY_6,
		Key_7 = GLFW_KEY_7,
		Key_8 = GLFW_KEY_8,
		Key_9 = GLFW_KEY_9,

		//Alphabet
		Key_A = GLFW_KEY_A,
		Key_B = GLFW_KEY_B,
		Key_C = GLFW_KEY_C,
		Key_D = GLFW_KEY_D,
		Key_E = GLFW_KEY_E,
		Key_F = GLFW_KEY_F,
		Key_G = GLFW_KEY_G,
		Key_H = GLFW_KEY_H,
		Key_I = GLFW_KEY_I,
		Key_J = GLFW_KEY_J,
		Key_K = GLFW_KEY_K,
		Key_L = GLFW_KEY_L,
		Key_M = GLFW_KEY_M,
		Key_N = GLFW_KEY_N,
		Key_O = GLFW_KEY_O,
		Key_P = GLFW_KEY_P,
		Key_Q = GLFW_KEY_Q,
		Key_R = GLFW_KEY_R,
		Key_S = GLFW_KEY_S,
		Key_T = GLFW_KEY_T,
		Key_U = GLFW_KEY_U,
		Key_V = GLFW_KEY_V,
		Key_W = GLFW_KEY_W,
		Key_X = GLFW_KEY_X,
		Key_Y = GLFW_KEY_Y,
		Key_Z = GLFW_KEY_Z,

		//Numpad
		Key_NP_0 = GLFW_KEY_KP_0,
		Key_NP_1 = GLFW_KEY_KP_1,
		Key_NP_2 = GLFW_KEY_KP_2,
		Key_NP_3 = GLFW_KEY_KP_3,
		Key_NP_4 = GLFW_KEY_KP_4,
		Key_NP_5 = GLFW_KEY_KP_5,
		Key_NP_6 = GLFW_KEY_KP_6,
		Key_NP_7 = GLFW_KEY_KP_7,
		Key_NP_8 = GLFW_KEY_KP_8,
		Key_NP_9 = GLFW_KEY_KP_9,
		Key_NP_ADD = GLFW_KEY_KP_ADD,
		Key_NP_DECIMAL = GLFW_KEY_KP_DECIMAL,
		Key_NP_DIVIDE = GLFW_KEY_KP_DIVIDE,
		Key_NP_ENTER = GLFW_KEY_KP_ENTER,
		Key_NP_EQUAL = GLFW_KEY_KP_EQUAL,
		Key_NP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
		Key_NP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,

		//Fn keys
		Key_F1 = GLFW_KEY_F1,
		Key_F2 = GLFW_KEY_F2,
		Key_F3 = GLFW_KEY_F3,
		Key_F4 = GLFW_KEY_F4,
		Key_F5 = GLFW_KEY_F5,
		Key_F6 = GLFW_KEY_F6,
		Key_F7 = GLFW_KEY_F7,
		Key_F8 = GLFW_KEY_F8,
		Key_F9 = GLFW_KEY_F9,
		Key_F10 = GLFW_KEY_F10,
		Key_F11 = GLFW_KEY_F11,
		Key_F12 = GLFW_KEY_F12,

		//Right Side
		Key_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
		Key_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
		Key_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
		Key_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
		Key_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,

		//Left Side
		Key_LEFT_ALT = GLFW_KEY_LEFT_ALT,
		Key_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
		Key_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
		Key_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
		Key_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,

		//Arrows
		Key_UP = GLFW_KEY_UP,
		Key_DOWN = GLFW_KEY_DOWN,
		Key_LEFT = GLFW_KEY_LEFT,
		Key_RIGHT = GLFW_KEY_RIGHT,

		//Functions
		Key_BACKSPACE = GLFW_KEY_BACKSPACE,
		Key_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
		Key_DELETE = GLFW_KEY_DELETE,
		Key_END = GLFW_KEY_END,
		Key_ENTER = GLFW_KEY_ENTER,
		Key_ESCAPE = GLFW_KEY_ESCAPE,
		Key_HOME = GLFW_KEY_HOME,
		Key_INSERT = GLFW_KEY_INSERT,
		Key_LAST = GLFW_KEY_LAST,
		Key_MENU = GLFW_KEY_MENU,
		Key_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
		Key_PAGE_UP = GLFW_KEY_PAGE_UP,
		Key_PAUSE = GLFW_KEY_PAUSE,
		Key_TAB = GLFW_KEY_TAB,
		Key_SPACE = GLFW_KEY_SPACE,

		//Symbols
		Key_APOSTROPHE = GLFW_KEY_APOSTROPHE,
		Key_BACKSLASH = GLFW_KEY_BACKSLASH,
		Key_COMMA = GLFW_KEY_COMMA,
		Key_EQUAL = GLFW_KEY_EQUAL,
		Key_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
		Key_MINUS = GLFW_KEY_MINUS,
		Key_PERIOD = GLFW_KEY_PERIOD,
		Key_SEMICOLON = GLFW_KEY_SEMICOLON,
		Key_FORWARDSLASH = GLFW_KEY_SLASH
    };

    class KeyboardController{
    private:
		GLFWwindow* window;
	public:
		//Assign Window
		KeyboardController(GLFWwindow* window);

		//check for key press
		bool KeyPressed(KeyboardButtonEnums key);
	};

    namespace Keys
    {
        //Delay to one key
        extern int LastKeyPressed;

        extern int LastCharecterPressed;

        //Update last Pressed
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

        //Update Last Typable Key
        static void character_callback(GLFWwindow* window, unsigned int codepoint);
    } // namespace Keys
    

} // namespace UnifiedEngine
