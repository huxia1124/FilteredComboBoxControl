#include "MainWindow.h"

MainWindow::MainWindow()
    : m_hWnd(nullptr)
{

}

BOOL MainWindow::Create(LPCTSTR lpszTitle, int cx, int cy)
{
    SIZE size = { cx, cy };
    return Create(lpszTitle, size);
}

BOOL MainWindow::Create(LPCTSTR lpszTitle, const SIZE& size)
{
    LPCTSTR szWindowClass = _T("MainWindow");

    WNDCLASSEXW wcex = { sizeof(WNDCLASSEX) };

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MainWindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = szWindowClass;
    wcex.cbWndExtra = sizeof(MainWindow*);

    RegisterClassExW(&wcex);

    m_hWnd = CreateWindowEx(WS_EX_CONTROLPARENT, szWindowClass, lpszTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, size.cx, size.cy, nullptr, nullptr, wcex.hInstance, nullptr);

    if (m_hWnd)
    {
        SetWindowLongPtr(m_hWnd, 0, reinterpret_cast<DWORD_PTR>(this));
    }

    
    return m_hWnd != nullptr;
}

void MainWindow::Show()
{
    ShowWindow(m_hWnd, SW_SHOW);
}

void MainWindow::RunMessageLoop()
{
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK MainWindow::MainWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    MainWindow* pThis = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, 0));
    if (pThis)
    {
        pThis->PreWndProc(hWnd, message, wParam, lParam);
    }

    switch (message)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}