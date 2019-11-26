#pragma once

static const int WINDOW_WIDTH = 800;	// 横画面サイズ
static const int WINDOW_HEIGHT = 600;	// 縦画面サイズ
static const int SCREEN_TYPE = 0;		// 0通常, 1擬似フルスク(比率を守ったまま最大サイズ), 2フルスクリーン

static const int FPS_RATE = 60;				// 設定したFPS
static const float RESOURCE_SECOND = 0.01f;	// リソースのロードに割く1フレームごとの秒数

// 製品版ビルドの場合はfalseにする
#define DEBUG true
