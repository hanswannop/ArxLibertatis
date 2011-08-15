
#include "input/SDLInputBackend.h"

#include <SDL.h>

#include "core/SDLWindow.h"
#include "io/Logger.h"

SDLInputBackend::SDLInputBackend() { }

SDLInputBackend::~SDLInputBackend() {
	
	if(SDLWindow::mainWindow && SDLWindow::mainWindow->input == this) {
		SDLWindow::mainWindow->input = NULL;
	}
}

static int sdlToArxKey[SDLK_LAST];

static int sdlToArxButton[4];

bool SDLInputBackend::init() {
	
	if(!SDLWindow::mainWindow) {
		LogError << "Cannot initialize SDL input without SDL window.";
		return false;
	}
	
	// SDL_ShowCursor(0); TODO
	
	SDLWindow::mainWindow->input = this;
	
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
	SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
	SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);
	SDL_EventState(SDL_JOYAXISMOTION, SDL_ENABLE);
	SDL_EventState(SDL_JOYBALLMOTION, SDL_ENABLE);
	SDL_EventState(SDL_JOYHATMOTION, SDL_ENABLE);
	SDL_EventState(SDL_JOYBUTTONDOWN, SDL_ENABLE);
	SDL_EventState(SDL_JOYBUTTONUP, SDL_ENABLE);
	
	std::fill_n(sdlToArxKey, ARRAY_SIZE(sdlToArxKey), -1);
	
	sdlToArxKey[SDLK_BACKSPACE] = Keyboard::Key_Backspace;
	sdlToArxKey[SDLK_TAB] = Keyboard::Key_Tab;
	// sdlToArxKey[SDLK_CLEAR] = -1; // TODO
	sdlToArxKey[SDLK_RETURN] = Keyboard::Key_Enter;
	sdlToArxKey[SDLK_PAUSE] = Keyboard::Key_Pause;
	sdlToArxKey[SDLK_ESCAPE] = Keyboard::Key_Escape;
	sdlToArxKey[SDLK_SPACE] = Keyboard::Key_Spacebar;
	// sdlToArxKey[SDLK_EXCLAIM] = -1; // TODO
	// sdlToArxKey[SDLK_QUOTEDBL] = -1; // TODO
	// sdlToArxKey[SDLK_HASH] = -1; // TODO
	// sdlToArxKey[SDLK_DOLLAR] = -1; // TODO
	// sdlToArxKey[SDLK_AMPERSAND] = -1; // TODO
	// sdlToArxKey[SDLK_QUOTE] = -1; // TODO
	// sdlToArxKey[SDLK_LEFTPAREN] = -1; // TODO
	// sdlToArxKey[SDLK_RIGHTPAREN] = -1; // TODO
	// sdlToArxKey[SDLK_ASTERISK] = -1; // TODO
	// sdlToArxKey[SDLK_PLUS] = -1; // TODO
	sdlToArxKey[SDLK_COMMA] = Keyboard::Key_Comma;
	sdlToArxKey[SDLK_MINUS] = Keyboard::Key_Minus;
	sdlToArxKey[SDLK_PERIOD] = Keyboard::Key_Period;
	sdlToArxKey[SDLK_SLASH] = Keyboard::Key_Slash;
	sdlToArxKey[SDLK_0] = Keyboard::Key_0;
	sdlToArxKey[SDLK_1] = Keyboard::Key_1;
	sdlToArxKey[SDLK_2] = Keyboard::Key_2;
	sdlToArxKey[SDLK_3] = Keyboard::Key_3;
	sdlToArxKey[SDLK_4] = Keyboard::Key_4;
	sdlToArxKey[SDLK_5] = Keyboard::Key_5;
	sdlToArxKey[SDLK_6] = Keyboard::Key_6;
	sdlToArxKey[SDLK_7] = Keyboard::Key_7;
	sdlToArxKey[SDLK_8] = Keyboard::Key_8;
	sdlToArxKey[SDLK_9] = Keyboard::Key_9;
	// sdlToArxKey[SDLK_COLON] = -1; // TODO
	sdlToArxKey[SDLK_SEMICOLON] = Keyboard::Key_Semicolon;
	// sdlToArxKey[SDLK_LESS] = -1; // TODO
	sdlToArxKey[SDLK_EQUALS] = Keyboard::Key_Equals;
	// sdlToArxKey[SDLK_GREATER] = -1; // TODO
	// sdlToArxKey[SDLK_QUESTION] = -1; // TODO
	// sdlToArxKey[SDLK_AT] = -1; // TODO
	sdlToArxKey[SDLK_LEFTBRACKET] = Keyboard::Key_LeftBracket;
	sdlToArxKey[SDLK_BACKSLASH] = Keyboard::Key_Backslash;
	sdlToArxKey[SDLK_RIGHTBRACKET] = Keyboard::Key_RightBracket;
	// sdlToArxKey[SDLK_CARET] = -1; // TODO
	// sdlToArxKey[SDLK_UNDERSCORE] = -1; // TODO
	// sdlToArxKey[SDLK_BACKQUOTE] = -1; // TODO
	sdlToArxKey[SDLK_a] = Keyboard::Key_A;
	sdlToArxKey[SDLK_b] = Keyboard::Key_B;
	sdlToArxKey[SDLK_c] = Keyboard::Key_C;
	sdlToArxKey[SDLK_d] = Keyboard::Key_D;
	sdlToArxKey[SDLK_e] = Keyboard::Key_E;
	sdlToArxKey[SDLK_f] = Keyboard::Key_F;
	sdlToArxKey[SDLK_g] = Keyboard::Key_G;
	sdlToArxKey[SDLK_h] = Keyboard::Key_H;
	sdlToArxKey[SDLK_i] = Keyboard::Key_I;
	sdlToArxKey[SDLK_j] = Keyboard::Key_J;
	sdlToArxKey[SDLK_k] = Keyboard::Key_K;
	sdlToArxKey[SDLK_l] = Keyboard::Key_L;
	sdlToArxKey[SDLK_m] = Keyboard::Key_M;
	sdlToArxKey[SDLK_n] = Keyboard::Key_N;
	sdlToArxKey[SDLK_o] = Keyboard::Key_O;
	sdlToArxKey[SDLK_p] = Keyboard::Key_P;
	sdlToArxKey[SDLK_q] = Keyboard::Key_Q;
	sdlToArxKey[SDLK_r] = Keyboard::Key_R;
	sdlToArxKey[SDLK_s] = Keyboard::Key_S;
	sdlToArxKey[SDLK_t] = Keyboard::Key_T;
	sdlToArxKey[SDLK_u] = Keyboard::Key_U;
	sdlToArxKey[SDLK_v] = Keyboard::Key_V;
	sdlToArxKey[SDLK_w] = Keyboard::Key_W;
	sdlToArxKey[SDLK_x] = Keyboard::Key_X;
	sdlToArxKey[SDLK_y] = Keyboard::Key_Y;
	sdlToArxKey[SDLK_z] = Keyboard::Key_Z;
	sdlToArxKey[SDLK_DELETE] = Keyboard::Key_Delete;
	sdlToArxKey[SDLK_KP0] = Keyboard::Key_NumPad0;
	sdlToArxKey[SDLK_KP1] = Keyboard::Key_NumPad1;
	sdlToArxKey[SDLK_KP2] = Keyboard::Key_NumPad2;
	sdlToArxKey[SDLK_KP3] = Keyboard::Key_NumPad3;
	sdlToArxKey[SDLK_KP4] = Keyboard::Key_NumPad4;
	sdlToArxKey[SDLK_KP5] = Keyboard::Key_NumPad5;
	sdlToArxKey[SDLK_KP6] = Keyboard::Key_NumPad6;
	sdlToArxKey[SDLK_KP7] = Keyboard::Key_NumPad7;
	sdlToArxKey[SDLK_KP8] = Keyboard::Key_NumPad8;
	sdlToArxKey[SDLK_KP9] = Keyboard::Key_NumPad9;
	sdlToArxKey[SDLK_KP_PERIOD] = Keyboard::Key_NumPoint;
	sdlToArxKey[SDLK_KP_DIVIDE] = Keyboard::Key_NumDivide;
	sdlToArxKey[SDLK_KP_MULTIPLY] = Keyboard::Key_NumMultiply;
	sdlToArxKey[SDLK_KP_MINUS] = Keyboard::Key_NumSubtract;
	sdlToArxKey[SDLK_KP_PLUS] = Keyboard::Key_NumAdd;
	sdlToArxKey[SDLK_KP_ENTER] = Keyboard::Key_NumPadEnter;
	// sdlToArxKey[SDLK_KP_EQUALS] = -1; // TODO
	sdlToArxKey[SDLK_UP] = Keyboard::Key_UpArrow;
	sdlToArxKey[SDLK_DOWN] = Keyboard::Key_DownArrow;
	sdlToArxKey[SDLK_RIGHT] = Keyboard::Key_RightArrow;
	sdlToArxKey[SDLK_LEFT] = Keyboard::Key_LeftArrow;
	sdlToArxKey[SDLK_INSERT] = Keyboard::Key_Insert;
	sdlToArxKey[SDLK_HOME] = Keyboard::Key_Home;
	sdlToArxKey[SDLK_END] = Keyboard::Key_End;
	sdlToArxKey[SDLK_PAGEUP] = Keyboard::Key_PageUp;
	sdlToArxKey[SDLK_PAGEDOWN] = Keyboard::Key_PageDown;
	sdlToArxKey[SDLK_F1] = Keyboard::Key_F1;
	sdlToArxKey[SDLK_F2] = Keyboard::Key_F2;
	sdlToArxKey[SDLK_F3] = Keyboard::Key_F3;
	sdlToArxKey[SDLK_F4] = Keyboard::Key_F4;
	sdlToArxKey[SDLK_F5] = Keyboard::Key_F5;
	sdlToArxKey[SDLK_F6] = Keyboard::Key_F6;
	sdlToArxKey[SDLK_F7] = Keyboard::Key_F7;
	sdlToArxKey[SDLK_F8] = Keyboard::Key_F8;
	sdlToArxKey[SDLK_F9] = Keyboard::Key_F9;
	sdlToArxKey[SDLK_F10] = Keyboard::Key_F10;
	sdlToArxKey[SDLK_F11] = Keyboard::Key_F11;
	sdlToArxKey[SDLK_F12] = Keyboard::Key_F12;
	sdlToArxKey[SDLK_F13] = Keyboard::Key_F13;
	sdlToArxKey[SDLK_F14] = Keyboard::Key_F14;
	sdlToArxKey[SDLK_F15] = Keyboard::Key_F15;
	sdlToArxKey[SDLK_NUMLOCK] = Keyboard::Key_NumLock;
	sdlToArxKey[SDLK_CAPSLOCK] = Keyboard::Key_CapsLock;
	sdlToArxKey[SDLK_SCROLLOCK] = Keyboard::Key_ScrollLock;
	sdlToArxKey[SDLK_RSHIFT] = Keyboard::Key_RightShift;
	sdlToArxKey[SDLK_LSHIFT] = Keyboard::Key_LeftShift;
	sdlToArxKey[SDLK_RCTRL] = Keyboard::Key_RightCtrl;
	sdlToArxKey[SDLK_LCTRL] = Keyboard::Key_LeftCtrl;
	sdlToArxKey[SDLK_RALT] = Keyboard::Key_RightAlt;
	sdlToArxKey[SDLK_LALT] = Keyboard::Key_LeftAlt;
	sdlToArxKey[SDLK_RMETA] = Keyboard::Key_RightWin;
	sdlToArxKey[SDLK_LMETA] = Keyboard::Key_LeftWin;
	sdlToArxKey[SDLK_LSUPER] = Keyboard::Key_RightWin;
	sdlToArxKey[SDLK_RSUPER] = Keyboard::Key_LeftWin;
	sdlToArxKey[SDLK_MODE] = Keyboard::Key_RightAlt;
	// sdlToArxKey[SDLK_COMPOSE] = -1; // TODO
	// sdlToArxKey[SDLK_HELP] = -1; // TODO
	sdlToArxKey[SDLK_PRINT] = Keyboard::Key_PrintScreen;
	// sdlToArxKey[SDLK_SYSREQ] = -1; // TODO
	// sdlToArxKey[SDLK_BREAK] = -1; // TODO
	// sdlToArxKey[SDLK_MENU] = -1; // TODO
	// sdlToArxKey[SDLK_POWER] = -1; // TODO
	// sdlToArxKey[SDLK_EURO] = -1; // TODO
	// sdlToArxKey[SDLK_UNDO] = -1; // TODO
	
	std::fill_n(sdlToArxButton, ARRAY_SIZE(sdlToArxButton), -1);
	
	sdlToArxButton[SDL_BUTTON_LEFT] = Mouse::Button_0;
	sdlToArxButton[SDL_BUTTON_MIDDLE] = Mouse::Button_1;
	sdlToArxButton[SDL_BUTTON_RIGHT] = Mouse::Button_2;
	
	wheel = 0;
	cursor = Vec2i::ZERO;
	std::fill_n(keyStates, ARRAY_SIZE(keyStates), false);
	std::fill_n(buttonStates, ARRAY_SIZE(buttonStates), false);
	std::fill_n(clickCount, ARRAY_SIZE(clickCount), 0);
	std::fill_n(unclickCount, ARRAY_SIZE(unclickCount), 0);
	
	return true;
}

bool SDLInputBackend::update() {
	
	
	if(SDLWindow::mainWindow) {
		SDLWindow::mainWindow->Tick();
	}
	
	currentWheel = wheel;
	std::copy(clickCount, clickCount + ARRAY_SIZE(clickCount), currentClickCount);
	std::copy(unclickCount, unclickCount + ARRAY_SIZE(unclickCount), currentUnclickCount);
	
	wheel = 0;
	std::fill_n(clickCount, ARRAY_SIZE(clickCount), 0);
	std::fill_n(unclickCount, ARRAY_SIZE(unclickCount), 0);
	
	return true;
}

void SDLInputBackend::acquireDevices() {
	SDL_WM_GrabInput(SDL_GRAB_ON);
}

void SDLInputBackend::unacquireDevices() {
	SDL_WM_GrabInput(SDL_GRAB_OFF);
}

void SDLInputBackend::getMouseCoordinates(int & absX, int & absY, int & wheelDir) const {
	absX = cursor.x, absY = cursor.y, wheelDir = currentWheel;
}

void SDLInputBackend::setMouseCoordinates(int absX, int absY) {
	SDL_WarpMouse(absX, absY);
}

bool SDLInputBackend::isMouseButtonPressed(int buttonId, int & deltaTime) const  {
	arx_assert(buttonId >= Mouse::ButtonBase && buttonId < Mouse::ButtonMax);
	deltaTime = 0; // TODO
	return buttonStates[buttonId - Mouse::ButtonBase];
}

void SDLInputBackend::getMouseButtonClickCount(int buttonId, int & numClick, int & numUnClick) const {
	arx_assert(buttonId >= Mouse::ButtonBase && buttonId < Mouse::ButtonMax);
	size_t i = buttonId - Mouse::ButtonBase;
	numClick = currentClickCount[i], numUnClick = currentUnclickCount[i];
}

bool SDLInputBackend::isKeyboardKeyPressed(int keyId) const {
	arx_assert(keyId >= Keyboard::KeyBase && keyId < Keyboard::KeyMax);
	return keyStates[keyId - Keyboard::KeyBase];
}

bool SDLInputBackend::getKeyAsText(int keyId, char & result) const {
	ARX_UNUSED(keyId), result = 'F';
	return true; // TODO implement
}

void SDLInputBackend::onInputEvent(const SDL_Event & event) {
	
	switch(event.type) {
		
		case SDL_KEYDOWN:
		case SDL_KEYUP: {
			SDLKey key = event.key.keysym.sym;
			if(key >= 0 && key < ARRAY_SIZE(sdlToArxKey) && sdlToArxKey[key] >= 0) {
				keyStates[sdlToArxKey[key] - Keyboard::KeyBase] = (event.key.state == SDL_PRESSED);
			}
			break;
		}
		
		case SDL_MOUSEMOTION: {
			cursor = Vec2i(event.motion.x, event.motion.y);
			break;
		}
		
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP: {
			Uint8 button = event.button.button;
			if(button == SDL_BUTTON_WHEELUP) {
				wheel++;
			} else if(button == SDL_BUTTON_WHEELDOWN) {
				wheel--;
			} else if(button < ARRAY_SIZE(sdlToArxButton) && sdlToArxButton[button] >= 0) {
				size_t i = sdlToArxButton[button] - Mouse::ButtonBase;
				if((event.button.state == SDL_PRESSED)) {
					buttonStates[i] = true, clickCount[i]++;
				} else {
					buttonStates[i] = false, unclickCount[i]++;
				}
			}
			break;
		}
		
		case SDL_JOYAXISMOTION:
		case SDL_JOYBALLMOTION:
		case SDL_JOYHATMOTION:
		case SDL_JOYBUTTONDOWN:
		case SDL_JOYBUTTONUP: break;
		
	}
	
}
