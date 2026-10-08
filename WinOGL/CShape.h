#pragma once
#include "pch.h"
#include "CVertex.h"

class CShape {
	//連れてきた。頂点の最初と最後を
private:
	CVertex* vertex_head;//CShapeクラスで再定義
	CVertex* vertex_tail;
	CShape* next_shape;
	CShape* pre_shape;
	bool close_flag;//bool型なに

public:
	CShape();~CShape();

	void AddVertex(float x, float y);
	void FreeVertex();

	float Distance(float x1, float y1, float x2, float y2);

	CVertex* GetVertexHead();
	CVertex* GetVertexTail();

	CShape* GetNext();
	void SetNext(CShape* new_next);
	CShape* GetPre();
	void SetPre(CShape* new_pre);

	bool GetClose();
	void SetClose(bool flag);

};
