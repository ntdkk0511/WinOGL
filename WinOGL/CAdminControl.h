#pragma once
#include <gl/GL.h>
#include "CVertex.h"
#include "CShape.h"

class CAdminControl {

private:
	CShape* shape_head;
	CShape* shape_tail;

public:
	CAdminControl();
	~CAdminControl();

	void AddShape();
	void AddVertex(float x, float y);
	void FreeShape();

	CShape* GetShapeHead();
	CShape* GetShapeTail();

	void Draw();

	float Distance(CVertex* v1,CVertex* v2);
};

