//  file-id: program344.c

#include <tchar.h>
#include <windows.h>

const TCHAR szWndClass[] = _T("Program344class");
BOOL   dFlag = FALSE;   // TRUE-->draw
HPEN   blackPen, yellowPen, redPen, greenPen, bluePen, eraserPen;
HBRUSH blackBrush, yellowBrush, redBrush, greenBrush, blueBrush, whiteBrush;
HPEN   pen;      // 現在のペン
HBRUSH brush;    // 現在のブラシ

LRESULT CALLBACK WndProc(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);  //ウィンドウプロシージャ　プロトタイプ

int WINAPI WinMain(
	HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {
	HWND     hWnd;
	WNDCLASS wc;
	MSG      msg;
	BOOL     bRet;

	wc.style = CS_HREDRAW | CS_VREDRAW;
	//  wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szWndClass;

	if (!RegisterClass(&wc)) { return FALSE; }

	hWnd = CreateWindow(
		szWndClass,
		_T("Program344のウィンドウ"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hWnd) { return FALSE; }

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (bRet = GetMessage(&msg, NULL, 0, 0)) {
		if (bRet == -1) { return FALSE; }
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	HDC    hdc;
	PAINTSTRUCT ps;
	RECT   rctDimension;
	static POINT  p = { 0, 0 }, pm = { 0, 0 };
	static BOOL dragged = FALSE;  // ドラッグ中であるか
	TCHAR  str[] = _T("[eraser]");
	TCHAR  sc[] = _T(" color of selected pen");
	TCHAR  buf[20];

	switch (msg) {
	case WM_CREATE:
		hdc = GetDC(hWnd);
		// ペン作成
		blackPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		yellowPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
		redPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		greenPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		bluePen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
		eraserPen = CreatePen(PS_SOLID, 10, RGB(255, 255, 255));
		// ブラシ作成
		blackBrush = CreateSolidBrush(RGB(0, 0, 0));
		yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
		redBrush = CreateSolidBrush(RGB(255, 0, 0));
		greenBrush = CreateSolidBrush(RGB(0, 255, 0));
		blueBrush = CreateSolidBrush(RGB(0, 0, 255));
		whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
		// intial setting
		pen = blackPen;
		brush = blackBrush;
		ReleaseDC(hWnd, hdc);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// パレットを作る
		SelectObject(hdc, blackPen);
		SelectObject(hdc, blackBrush);
		Rectangle(hdc, 10, 10, 30, 30);  // black
		SelectObject(hdc, yellowBrush);
		Rectangle(hdc, 30, 10, 50, 30);  // yellow
		SelectObject(hdc, redBrush);
		Rectangle(hdc, 50, 10, 70, 30);  // red
		SelectObject(hdc, greenBrush);
		Rectangle(hdc, 70, 10, 90, 30);  // green
		SelectObject(hdc, blueBrush);
		Rectangle(hdc, 90, 10, 110, 30);  // blue
		SelectObject(hdc, whiteBrush);
		Rectangle(hdc, 115, 10, 135, 30);  // eraser

		TextOut(hdc, 137, 15, str, _tcslen(str));
		// 選択ペンを描く
		SelectObject(hdc, blackPen);
		SelectObject(hdc, brush);
		Rectangle(hdc, 210, 10, 235, 30);  // pen
		TextOut(hdc, 237, 15, sc, _tcslen(sc));

		EndPaint(hWnd, &ps);
		break;

	case  WM_LBUTTONDOWN:   // マウスの左ボタンが押された
		p.x = LOWORD(lParam);
		p.y = HIWORD(lParam);
		// 色選択
		if (10 < p.x && p.x < 30 && 10 < p.y && p.y < 30){
			pen = blackPen;
			brush = blackBrush;
		}
		else if (30 < p.x &&p.x < 50 && 10 < p.y && p.y < 30){
			pen = yellowPen;
			brush = yellowBrush;
		}
		else if (50 < p.x && p.x < 70 && 10 < p.y && p.y < 30){
			pen = redPen;
			brush = redBrush;
		}
		else if (70 < p.x && p.x < 90 && 10 < p.y && p.y < 30){
			pen = greenPen;
			brush = greenBrush;
		}
		else if (90 < p.x && p.x < 110 && 10 < p.y && p.y < 30){
			pen = bluePen;
			brush = blueBrush;
		}
		else if (115 < p.x && p.x < 135 && 10 < p.y && p.y < 30){
			pen = eraserPen;
			brush = whiteBrush;
		}
		dFlag = TRUE;
		break;

	case  WM_LBUTTONUP:  // マウスの左ボタンが離された
		hdc = GetDC(hWnd);
		// 選択ペンを描く
		SelectObject(hdc, blackPen);
		SelectObject(hdc, brush);
		Rectangle(hdc, 210, 10, 235, 30);  // pen
		TextOut(hdc, 237, 15, sc, _tcslen(sc));
		ReleaseDC(hWnd, hdc);
		dFlag = FALSE;
		break;

	case  WM_MOUSEMOVE:   // マウスの位置が移動した
		hdc = GetDC(hWnd);
		pm.x = LOWORD(lParam);
		pm.y = HIWORD(lParam);
		wsprintf(buf, _T("(%4d %4d)"), (int)pm.x, (int)pm.y);
		TextOut(hdc, 410, 15, buf, _tcslen(buf));
		if (dFlag == TRUE){
			SelectObject(hdc, pen);
			MoveToEx(hdc, p.x, p.y, NULL);
			LineTo(hdc, pm.x, pm.y);
			p.x = pm.x;
			p.y = pm.y;
		}
		ReleaseDC(hWnd, hdc);
		break;

	case  WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return  DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return 0;
}
