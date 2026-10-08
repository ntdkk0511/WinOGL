// WinOGLView.cpp : CWinOGLView クラスの実装
#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include <gl/GL.h>
#include "WinOGL.h"
#endif

#include "WinOGLDoc.h"
#include "WinOGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWinOGLView

IMPLEMENT_DYNCREATE(CWinOGLView, CView)

BEGIN_MESSAGE_MAP(CWinOGLView, CView)
	ON_WM_LBUTTONDOWN()
//	ON_WM_ACTIVATE()
ON_WM_CREATE()
ON_WM_DESTROY()
ON_WM_ERASEBKGND()
ON_WM_SIZE()
END_MESSAGE_MAP()

// CWinOGLView コンストラクション/デストラクション

CWinOGLView::CWinOGLView() noexcept
{
	//ここで初期化とかしとけば，最初からその値が入る便利なヤツ:コンストラクタ
	x_Ldown = 0.0f;
	y_Ldown = 0.0f;
}

CWinOGLView::~CWinOGLView()
{
}

BOOL CWinOGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CWinOGLView 描画
//OnDrow関数

void CWinOGLView::OnDraw(CDC* pDC) {
	CWinOGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	wglMakeCurrent(pDC->m_hDC, m_hRC);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT /* | GL_DEPTH_BUFFER_BIT*/);

	AC.Draw();	
	//glColor3f(1.0, 1.0, 1.0);
	//glPointSize(5.0);
	//glBegin(GL_POINTS);
	//glVertex2f(x_Ldown, y_Ldown);
	//glEnd();
	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(pDC->m_hDC, NULL);
}

// CWinOGLView の診断

#ifdef _DEBUG
void CWinOGLView::AssertValid() const
{
	CView::AssertValid();
}

void CWinOGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWinOGLDoc* CWinOGLView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWinOGLDoc)));
	return (CWinOGLDoc*)m_pDocument;
}
#endif //_DEBUG


// CWinOGLView メッセージ ハンドラー

void CWinOGLView::OnLButtonDown(UINT nFlags, CPoint point) {
	// 描画領域の大きさを取得
	CRect rect;
	GetClientRect(rect);

	x_Ldown = point.x;
	y_Ldown = point.y;
	//正規化
	float seiki_x = x_Ldown/rect.Width();
	float seiki_y = (rect.Height() - y_Ldown) / rect.Height();
	//ワールド座標系
	float world_x = (seiki_x - 0.5f)*2.0f;
	float world_y = (seiki_y - 0.5f)*2.0f;
	//描画のために代入
	x_Ldown = world_x;
	y_Ldown = world_y;
	
	//横長の場合
	if (rect.Width() - rect.Height() >= 0) {
		float aspect = rect.Width() / rect.Height();
		x_Ldown = x_Ldown * aspect;
	}
	else {
		float aspect = rect.Height() / rect.Width();
		y_Ldown = y_Ldown * aspect;
	}
	AC.AddVertex(x_Ldown, y_Ldown);
	RedrawWindow();
	CView::OnLButtonDown(nFlags, point);
}

int CWinOGLView::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	PIXELFORMATDESCRIPTOR pfd =
	{
	sizeof(PIXELFORMATDESCRIPTOR),
	1,
	PFD_DRAW_TO_WINDOW |
	PFD_SUPPORT_OPENGL |
	PFD_DOUBLEBUFFER,
	PFD_TYPE_RGBA,
	32,
	0,0,0,0,0,0,
	0,0,0,0,0,0,0,
	24,
	0,0,
	PFD_MAIN_PLANE,
	0,
	0,0,0
	};
	CClientDC clientDC(this);
	int pixelFormat = ChoosePixelFormat(clientDC.m_hDC,
		&pfd);
	SetPixelFormat(clientDC.m_hDC, pixelFormat, &pfd);
	m_hRC = wglCreateContext(clientDC.m_hDC);

	return 0;
}

void CWinOGLView::OnDestroy() {
	CView::OnDestroy();
	wglDeleteContext(m_hRC);

}

BOOL CWinOGLView::OnEraseBkgnd(CDC* pDC) {
	return true;
}

//OnSize関数

void CWinOGLView::OnSize(UINT nType, int cx, int cy) {
	CView::OnSize(nType, cx, cy);
	CClientDC clientDC(this);
	wglMakeCurrent(clientDC.m_hDC, m_hRC);
	glViewport(0, 0, cx, cy);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	double aspect;

	//課題1:視体積の設定
	if (cx == 0) { cx = 1; }
	if (cy == 0) { cy = 1; }
	if (cx >= cy) {
		aspect = cx / cy;
		glOrtho(-aspect, aspect, -1.0, 1.0, -100.0, 100.0);
	}
	else {
		aspect = cy / cx;
		glOrtho(-1.0,1.0, -aspect,aspect, -100.0, 100.0);
	}

	glMatrixMode(GL_MODELVIEW);
	RedrawWindow();
	wglMakeCurrent(clientDC.m_hDC, NULL);
}
