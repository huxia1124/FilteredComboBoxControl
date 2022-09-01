#pragma once

#include "framework.h"

class MainWindow
{
public:
	MainWindow();

	BOOL Create(LPCTSTR lpszTitle, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT);
	BOOL Create(LPCTSTR lpszTitle, const SIZE& size);
	void Show();
	void RunMessageLoop();

	HWND GetHWnd() const { return m_hWnd; }

protected:

	virtual LRESULT PreWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return 0;
	}

	static LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
};

