#pragma once
#include<Component.h>

///<summary>
///	文字表示用クラス
///</summary>
class Text : public Component {

public:
	Text();
	Text(GameObject *body);
	virtual	~Text();

	virtual	void Draw()override;

	// 表示したい文字を入れる
	void SetText(const char* text);
	void SetText(const std::string &text);

	// 文字の色を変える
	void SetColor(int red,  int green, int blue);

	/*
	フォントを作る(thickは0～9まで、それぞれ引数に-1を入れるとデフォルト設定になる)
	DX_FONTTYPE_NORMAL　　　　　　　　　: ノーマルフォント
	DX_FONTTYPE_EDGE　　　　　　　　　　: エッジつきフォント
	DX_FONTTYPE_ANTIALIASING　　　　　　: アンチエイリアスフォント
	DX_FONTTYPE_ANTIALIASING_4X4　　　　: アンチエイリアスフォント(4x4サンプリング)
	DX_FONTTYPE_ANTIALIASING_8X8　　　　: アンチエイリアスフォント(8x8サンプリング)
	DX_FONTTYPE_ANTIALIASING_EDGE_4X4　 : アンチエイリアス＆エッジ付きフォント(4x4サンプリング)
	DX_FONTTYPE_ANTIALIASING_EDGE_8X8　 : アンチエイリアス＆エッジ付きフォント(8x8サンプリング) )
	*/
	void CreateFontHandle(int size = -1, int thick = -1, int fontType = -1);

	// 作成したフォントを読み込み使用する(ファイル名、縁の太さ)
	void LoadFontHandle(const char* fileName, int edgeSize);

private:
	int m_fontHandle;		// テキストのハンドル
	int m_colorHandle;		// 色のハンドル
	std::string m_text;		// 表示するテキスト

};
