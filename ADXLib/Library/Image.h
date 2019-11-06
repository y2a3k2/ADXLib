#pragma once
#include<DxMath.h>
#include<Component.h>

///<summary>
///	2D画像の表示用クラス
///	単純な表示しかできず、変形させることは不可能
///	UIや一枚絵を表示する時に処理を軽く表示できる
///</summary>
class Image : public Component {

public:
	Image();
	Image(GameObject *body);
	virtual	~Image();
	virtual	void Draw()override;

	// ファイルをロードする
	virtual	void Load(const char *fileName);
	// 画像の中心点を変更する
	void SetCenter(int cx, int cy);
	// 画像の色の値を減らす
	void SetColor(unsigned char red, unsigned char green, unsigned char blue);
	// 画像の透明度を適応するかどうか(初期値はtrue)
	void SetTrans(bool flag);

	// ノーブレンド（デフォルト）
	void SetBlendDefault();
	// αブレンド
	void SetBlendAlpha(unsigned char pal);
	// 加算ブレンド
	void SetBlendAdd(unsigned char pal);
	// 減算ブレンド
	void SetBlendSub(unsigned char pal);
	// 乗算ブレンド
	void SetBlendMula(unsigned char pal);
	// 反転ブレンド
	void SetBlendInvsrc(unsigned char pal);
	// 乗算済みα用のαブレンド
	void SetBlendPmaAlpha(unsigned char pal);
	// 乗算済みα用の加算ブレンド
	void SetBlendPmaAdd(unsigned char pal);
	// 乗算済みα用の減算ブレンド
	void SetBlendPmaSub(unsigned char pal);
	// 乗算済みα用の反転ブレンド
	void SetBlendPmaInvsrc(unsigned char pal);

	// 画像のサイズ
	const INT_VECTOR2 &GetSize();
	// 画像のWorld座標
	VECTOR GetWorldPosition();

protected:
	// 画像を消す
	inline void Unload();


protected:
	int m_handle;				// グラフィックハンドル
	INT_VECTOR2 m_center;		// 画像の中心
	INT_VECTOR2 m_size;			// 画像のサイズ
	COLOR m_color;				// 画像の色(デフォルトは255,255,255)
	bool m_trans;				// 画像の透過色を反映するか
	int m_blendMode;			// ブレンドモード
	unsigned char m_blendPal;	// ブレンドの強さ

};
