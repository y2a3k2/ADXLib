#pragma once
#include<Component.h>

class Movie :public Component {

public:
	Movie();
	Movie(GameObject *body);
	virtual	~Movie();	
	virtual	void Draw()override;
	virtual void Load(const char* fileName);

protected:
	inline void Unload();

protected:
	int m_handle;

};
