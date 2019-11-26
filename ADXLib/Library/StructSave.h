#pragma once
#include<stdio.h>
#include<string>

///	<summary>
///	構造体をセーブする。初めにファイル階層を入れなければ使えない
///	</summary>
template<typename T> class StructSave {

public:
	StructSave(const char *fileName) { m_fileName = fileName; }
	virtual	~StructSave() {};

	// 書き込み
	void Write(const T &t) {
		FILE *pFile;
		T data = t;
		// ファイルを開けなければ
		if (fopen_s(&pFile, m_fileName.c_str(), "w") != 0) {
			// ファイルを新規作成
			fopen_s(&pFile, m_fileName.c_str(), "w+");
		}
		fwrite(&t, sizeof(T), 1, pFile);		// SaveData構造体の中身を書き込み。
		fclose(pFile);							// ファイルを閉じる
	}

	// 読み取り
	T Read() {
		FILE *pFile;
		T data;
		// ファイルが開けなければ
		if (fopen_s(&pFile, m_fileName.c_str(), "r") != 0) {
			// ファイルを新規作成
			fopen_s(&pFile, m_fileName.c_str(), "w+");
		}
		fread(&data, sizeof(T), 1, pFile);		// freadだと書き込み。
		fclose(pFile);							// ファイルを閉じる
		return data;
	}

private:
	std::string m_fileName;

};
