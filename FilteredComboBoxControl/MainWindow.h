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

	virtual void PreWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	}
	virtual void PostWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	}

	static LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
};

