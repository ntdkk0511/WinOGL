#include "pch.h"
#include "CVertex.h"

CVertex::CVertex() {
	x = 0.0;
	y = 0.0;
	next_vertex = NULL;
	pre_vertex = NULL;
}

CVertex::CVertex(float new_x, float new_y, CVertex* new_next) {
	SetXY(new_x, new_y);
	SetNext(new_next);
}

CVertex::~CVertex() {

}

void CVertex::SetXY(float new_x, float new_y) {
	x = new_x;
	y = new_y;
}

float CVertex::GetX() {
	return x;
}

float CVertex::GetY() {
	return y;
}

//次のセルを参照できる
void CVertex::SetNext(CVertex* new_next) {
	next_vertex = new_next;
}

CVertex* CVertex::GetNext() {
	return next_vertex;
}

//前のセルを参照できる
void CVertex::SetPre(CVertex* new_pre) {
	pre_vertex = new_pre;
}

CVertex* CVertex::GetPre() {
	return pre_vertex;
}

void CVertex::FreeVertex() {
	CVertex* nowV = this;
	while (nowV != NULL) {
		CVertex* del_cell = nowV;
		nowV = nowV->GetNext();
		delete del_cell;
	}
}

