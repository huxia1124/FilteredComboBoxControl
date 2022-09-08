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
    wcex.cbWndExtra = sizeof(MainWindow*);
    wcex.hInstance = GetModuleHandle(nullptr);
    wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszClassName = szWindowClass;

    RegisterClassExW(&wcex);

    m_hWnd = CreateWindowEx(WS_EX_CONTROLPARENT, szWindowClass, lpszTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, size.cx, size.cy, nullptr, nullptr, wcex.hInstance, this);
    
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

    LRESULT result = 0;
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
    case WM_CREATE:
        {
            LPCREATESTRUCT pCS = reinterpret_cast<LPCREATESTRUCT>(lParam);
            pThis = reinterpret_cast<MainWindow*>(pCS->lpCreateParams);
            result = DefWindowProc(hWnd, message, wParam, lParam);

            if (result != -1)
            {
                SetWindowLongPtr(hWnd, 0, reinterpret_cast<DWORD_PTR>(pThis));
                if (pThis)
                {
                    pThis->PostWndProc(hWnd, message, wParam, lParam);
                }
            }
        }
        break;
    default:
        result = DefWindowProc(hWnd, message, wParam, lParam);
        if (pThis)
        {
            pThis->PostWndProc(hWnd, message, wParam, lParam);
        }
    }
    return result;
}