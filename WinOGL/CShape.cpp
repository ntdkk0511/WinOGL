#include "pch.h"
#include "CShape.h"
#include "CVertex.h"
#include <cmath>

CShape::CShape() {
	vertex_head = NULL;
	vertex_tail = NULL;
	next_shape = NULL;
	pre_shape = NULL;
	close_flag = false;
}

CShape::~CShape() {
	void FreeVertex();
}

void CShape::FreeVertex() {
	if (vertex_head != NULL) {
		vertex_head->FreeVertex();
		vertex_head = NULL;
		vertex_tail = NULL;
	}
}


float CShape::Distance(float x1, float y1, float x2, float y2) {
	float dx = x1 - x2;
	float dy = y1 - y2;
	return std::sqrt(dx * dx + dy * dy);
}

void CShape::AddVertex(float x, float y){//(x,y)クリックされたら
	if (close_flag) {//完成した図形なら何もしない
		return;
	}
	if (vertex_head == NULL) {//1個目の点のとき
		CVertex* n = new CVertex(x, y, NULL);//おにゅーの新しい点n(x,y)を追加
		vertex_head = n;//始点として登録
		vertex_tail = n;//末尾としても登録
		return;
	}
	//2個目以降の点は距離が始点に近かったら図形閉じる
	float hantei = 0.08f;//閾値
	float dist = Distance(vertex_head->GetX(), vertex_head->GetY(), x, y);//引数として，始点のX,Y座標をGetし，あと今打った（x,y）が要る

	//閾値より近いところに点が打たれたら
	if (dist <= hantei) {
		CVertex* n = new CVertex(vertex_head->GetX(), vertex_head->GetY(), NULL);//始点を登録しちゃう
		//リストの末尾につなぐ【なにこれ】
		vertex_tail->SetNext(n);
		n->SetPre(vertex_tail);
		vertex_tail = n;

		close_flag = true;//完成フラグ
	}
	else {//近くなければ
		CVertex* n = new CVertex(x, y, NULL);//普通に新しい点追加
		//リストの末尾に繋ぐ【なにこれ】
		vertex_tail->SetNext(n);
		n->SetPre(vertex_tail);
		vertex_tail = n;
	}
}

CVertex* CShape::GetVertexHead() { return vertex_head; }
CVertex* CShape::GetVertexTail() { return vertex_tail; }

CShape* CShape::GetNext() {return next_shape; }
void CShape::SetNext(CShape* new_next) { next_shape = new_next; }
CShape* CShape::GetPre(){return pre_shape; }
void CShape::SetPre(CShape* new_pre){ pre_shape = new_pre; }

bool CShape::GetClose() { return close_flag; }
void CShape::SetClose(bool flag){ close_flag = flag; }

