#include "Test3d.h"

Test3d::Test3d() :
	SceneBase("Test3d") {

}

Test3d::~Test3d() {

}

void Test3d::Initialize() {

	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 10), VGet(0, 0, 0));
}

void Test3d::Update() {


	DrawSphere3D(VGet(0, 0, 0), 80.0f, 32, GetColor(255, 0, 0), GetColor(255, 255, 255), TRUE);
}
