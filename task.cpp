#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#include <math.h>
#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
using namespace std;
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

void swap(int& x1, int& y1, int& x2, int& y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}
int Round(double x) {
    return (int)x + 0.5;
}

void drawLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c) {
    int dx = x1 - x2;
    int dy = y1 - y2;
    if (abs(dx) > abs(dy)) {
        if (x1 > x2) {
            swap(x1,y1,x2,y2);

        }
        SetPixel(hdc, x1, y1, c);
        for (int x = x1 + 1; x <= x2; ++x) {
            double y = (1.0 * dy / dx) * (x - x1) + y1;
            SetPixel(hdc, x, Round(y), c);

        }
    }
    else {
        if (y1 > y2) {
            swap(x1, y1, x2, y2);

        }
        SetPixel(hdc, x1, y1, c);
        for (int y = y1 + 1; y <= y2; ++y) {
            double x = (1.0 * dx / dy) * (y - y1) + x1;
            SetPixel(hdc, Round(x), y, c);

        }
    }

}
void draw8lines(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int d = Round(R / sqrt(2));
    drawLine(hdc, xc, yc, xc + R, yc , c);
    drawLine(hdc, xc, yc, xc - R, yc , c);
    drawLine(hdc, xc, yc, xc , yc + R, c);
    drawLine(hdc, xc, yc, xc , yc - R, c);
    drawLine(hdc, xc, yc, xc + d, yc + d, c);
    drawLine(hdc, xc, yc, xc - d, yc - d, c);
    drawLine(hdc, xc, yc, xc - d, yc + d, c);
    drawLine(hdc, xc, yc, xc + d, yc - d, c);

}
void draw8points(HDC hdc, int xc, int yc, int x, int y, COLORREF c) {
    SetPixel(hdc, x + xc, y + yc, c);
    SetPixel(hdc, -x + xc, y + yc, c);
    SetPixel(hdc, x + xc, -y + yc, c);
    SetPixel(hdc, -x + xc, -y + yc, c);

    SetPixel(hdc, y + xc, x + yc, c);
    SetPixel(hdc, -y + xc, x + yc, c);
    SetPixel(hdc, y + xc, -x + yc, c);
    SetPixel(hdc, -y + xc, -x + yc, c);

}

void DrawCirclePolar(HDC hdc, int xc, int yc, int R, COLORREF c) {
    int x = R, y = 0;
    double theta = 0;
    double dtheta = 1.0 / R;
    draw8points(hdc, xc, yc, x, y, c);
    draw8lines(hdc, xc, yc, R,c);
    while(x>y) {
        theta += dtheta;
        x = Round(R * cos(theta));
        y = Round(R * sin(theta));

        draw8points(hdc, xc, yc, x, y, c);

    }
}
int xx1 , yy1 , xx2 , yy2 ,r;
LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc = GetDC(hwnd);

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:

        xx1 = GET_X_LPARAM(lParam);
        yy1 = GET_Y_LPARAM(lParam);
        break;
    case WM_RBUTTONDOWN:

        xx2 = GET_X_LPARAM(lParam);
        yy2 = GET_Y_LPARAM(lParam);

         r = Round(sqrt((xx1 - xx2) * (xx1 - xx2) + (yy1 - yy2) * (yy1 - yy2)));

        DrawCirclePolar(hdc, xx1, yy1, r, RGB(0, 0, 0));

        break;



    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0;
}
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);
    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
    if (!RegisterClassEx(&wincl))
        return 0;
    hwnd = CreateWindowEx(0, szClassName, _T("Code::Blocks Template Windows App"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 544, 375, HWND_DESKTOP, NULL, hThisInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}
