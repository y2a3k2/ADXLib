#include "InputManager.h"

InputManager * InputManager::GetInstance() {

	static InputManager *inst = nullptr;

	if (inst == nullptr) {
		inst = new InputManager();
	}
	return inst;
}

void InputManager::Update() {

	/* キー */
	for (int i = 0; i < 256; i++) {
		m_oldKey[i] = m_key[i];
	}
	GetHitKeyStateAll(m_key);

	/* ジョイパッド */
	for (int i = 0; i < 4; i++) {
		m_oldJoyPad[i] = m_joyPad[i];
		GetJoypadXInputState(GET_CONTROLLER[i], &m_joyPad[i]);
	}
}

void InputManager::SetJoyPadDeadZone(int padId, double zone) {

	// ありえない数値が来た場合
	if (padId < 0 || padId >= 4)
		return;

	SetJoypadDeadZone(GET_CONTROLLER[padId], zone);
}

bool InputManager::GetKey(int key) {

	// ありえない数値が来た場合
	if (key < 0 || key >= 256)
		return false;

	return GetSub(m_key[key]);
}

bool InputManager::GetKeyUp(int key) {

	// ありえない数値が来た場合
	if (key < 0 || key >= 256)
		return false;

	// 前のフレームだけ押した判定があるならtrue
	return (!GetSub(m_key[key]) && GetSub(m_oldKey[key]));
}

bool InputManager::GetKeyDown(int key) {

	// ありえない数値が来た場合
	if (key < 0 || key >= 256)
		return false;
	// 今のフレームだけ押した判定があるならtrue
	return (GetSub(m_key[key]) && !GetSub(m_oldKey[key]));
}

bool InputManager::GetPadButton(int button, int padId) {

	// ありえない数値が来た場合
	if (padId < 0 || padId >= 4)
		return false;
	if (button < 0 || button >= 16)
		return false;

	return GetSub(m_joyPad[padId].Buttons[button]);
}

bool InputManager::GetPadButtonUp(int button, int padId) {

	// ありえない数値が来た場合
	if (padId < 0 || padId >= 4)
		return false;
	if (button < 0 || button >= 16)
		return false;

	return (!GetSub(m_joyPad[padId].Buttons[button]) && GetSub(m_oldJoyPad[padId].Buttons[button]));
}

bool InputManager::GetPadButtonDown(int button, int padId) {

	// ありえない数値が来た場合
	if (padId < 0 || padId >= 4)
		return false;
	if (button < 0 || button >= 16)
		return false;

	return (GetSub(m_joyPad[padId].Buttons[button]) && !GetSub(m_oldJoyPad[padId].Buttons[button]));
}

VECTOR2 InputManager::GetPadStickLeft(int padId) {

	// ありえない数値が来た場合
	if (padId < 0 || padId >= 4)
		return VECTOR2(0, 0);

	return VECTOR2(DxMath::InverseLerp(-32768, 32767, m_joyPad[padId].ThumbLX),
		DxMath::InverseLerp(-32768, 32767, m_joyPad[padId].ThumbLY));
}

VECTOR2 InputManager::GetPadStickRight(int padId) {

	// ありえない数値が来た場合
	if (padId < 0 || padId >= 4)
		return VECTOR2(0, 0);

	return VECTOR2(DxMath::InverseLerp(-32768, 32767, m_joyPad[padId].ThumbRX),
		DxMath::InverseLerp(-32768, 32767, m_joyPad[padId].ThumbRY));
}

float InputManager::GetPadTriggerLeft(int padId) {

	// ありえない数値が来た場合
	if (padId < 0 || padId >= 4)
		return 0;

	return DxMath::InverseLerp(0, 255, m_joyPad[padId].LeftTrigger);
}

float InputManager::GetPadTriggerRight(int padId) {

	// ありえない数値が来た場合
	if (padId < 0 || padId >= 4)
		return 0;

	return DxMath::InverseLerp(0, 255, m_joyPad[padId].RightTrigger);
}

InputManager::InputManager()
	:SingletonObject(this) {
}

InputManager::~InputManager() {

}

bool InputManager::GetSub(char value) {

	return (value == 1);
}
