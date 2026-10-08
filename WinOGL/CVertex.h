#pragma once

class CVertex {
public:
	CVertex();
	CVertex(float new_x, float new_y, CVertex* new_next);
	~CVertex();

//privateには変数・publicには関数

private:
	float x;
	float y;
	CVertex* next_vertex;
	CVertex* pre_vertex;//前の点を指す

public:
	float GetX();
	float GetY();
	void SetXY(float new_x, float new_y);

	CVertex* GetNext();
	void SetNext(CVertex* new_next);
	CVertex* GetPre();
	void SetPre(CVertex* new_pre);

	void FreeVertex();



};