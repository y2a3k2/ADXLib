#pragma once
#include<DxLib.h>
#include<SingletonObject.h>
#include<DxMath.h>

class InputManager : public SingletonObject {

public:
	static InputManager *GetInstance();

	void Update()override;

	/* キーボード入力 */
	bool GetKey(int key);
	bool GetKeyUp(int key);
	bool GetKeyDown(int key);

	/* ゲームパッド入力 */
	bool GetPadButton(int button, int padId = 0);
	bool GetPadButtonUp(int button, int padId = 0);
	bool GetPadButtonDown(int button, int padId = 0);
	VECTOR2 GetPadStickLeft(int padId = 0);
	VECTOR2 GetPadStickRight(int padId = 0);
	float GetPadTriggerLeft(int padId = 0);
	float GetPadTriggerRight(int padId = 0);

	// ゲームパッドのスティックのゆとりを指定する
	void SetJoyPadDeadZone(int padId, double zone);

private:
	InputManager();
	~InputManager();

	bool GetSub(char value);

	const int GET_CONTROLLER[4] = { DX_INPUT_PAD1,DX_INPUT_PAD2,DX_INPUT_PAD3,DX_INPUT_PAD4 };

	char m_key[256];
	char m_oldKey[256];

	XINPUT_STATE m_joyPad[4];
	XINPUT_STATE m_oldJoyPad[4];
};
