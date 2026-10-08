#include "pch.h"
#include "CAdminControl.h"
#include "CVertex.h"
#include "CShape.h"

CAdminControl::CAdminControl() {
	shape_head = NULL;
	shape_tail = NULL;
}

CAdminControl::~CAdminControl() {
	FreeShape();//ここにFreeVertexいれないといけないのかわからないもしかしていらないのでは
}

//後でshapeを捜索してaddvertexを呼び出すように変えてもいいらしい
void CAdminControl::AddShape() {
	CShape* new_shape = new CShape();
	if (shape_head == NULL) {
		shape_head = new_shape;
		shape_tail = new_shape;
	}
	else {
		shape_tail->SetNext(new_shape);
		new_shape->SetPre(shape_tail);
		shape_tail = new_shape;
	}
}

void CAdminControl::AddVertex(float x, float y) {
	if (shape_tail == NULL || shape_tail->GetClose()) {
		AddShape();
	}
	shape_tail->AddVertex(x, y);
}

void CAdminControl::FreeShape() {
	CShape* nowS = shape_head;
	while (nowS != NULL) {
		CShape* del_shape = nowS;
		nowS = nowS->GetNext();
		delete del_shape;
	}
	shape_head = NULL;
	shape_tail = NULL;
}

//以下もうなにをしているかてんでわからない
void CAdminControl::Draw() {
	if (shape_head == NULL) {//図形がなければなにもしない
		return;
	}

	for (CShape* nowS = shape_head; nowS != NULL; nowS = nowS->GetNext()) {//図形のリストヘッドからNULLまでGetNext()で探索
		CVertex* v_head = nowS->GetVertexHead();//今にている図形Sの始点を確認してv_headにいれる
		if (v_head == NULL) continue;

		GLenum mode;
		if (nowS->GetClose()) {
			mode = GL_LINE_LOOP;
		}
		else {
			mode = GL_LINE_STRIP;
		}

		//線の描画
		glColor3f(1.0f, 1.0f, 1.0f);
		glLineWidth(2.0f);
		glBegin(mode);
		for (CVertex* nowV = v_head; nowV != NULL; nowV = nowV->GetNext()) {
			glVertex2f(nowV->GetX(), nowV->GetY());
		}
		glEnd();

		//点の描画
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		for (CVertex* nowV = v_head; nowV != NULL; nowV = nowV->GetNext()) {
			glVertex2f(nowV->GetX(), nowV->GetY());
		}
		glEnd();
	}

}

