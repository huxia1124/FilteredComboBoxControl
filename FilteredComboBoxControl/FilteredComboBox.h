#pragma once

#define     CB_SET_STRING_TAG		(WM_USER + 101)
#define     CB_DELETE_STRING_TAG	(WM_USER + 102)
#define     CB_ADD_FILTER			(WM_USER + 103)
#define     CB_ADD_FILTER_CHOICE	(WM_USER + 104)
#define     CB_SET_FILTER_MULTI_SELECTION	(WM_USER + 105)
#define     CB_SET_FILTER_UI_WIDTH	(WM_USER + 106)
#define     CB_PARSE_TABS			(WM_USER + 107)
#define     CB_CALCULATE_AUTO_WIDTH			(WM_USER + 108)
#define     CB_SET_EMPTY_TEXT		(WM_USER + 110)
#define     CB_AUTO_RESET_FILTERS	(WM_USER + 111)
#define     CB_DELETE_ALL_FILTERS	(WM_USER + 112)

struct COMBOBOX_STRING_PAIR
{
	COMBOBOX_STRING_PAIR(LPCTSTR s1, LPCTSTR s2) : lpsz1(s1), lpsz2(s2)
	{}
	LPCTSTR lpsz1;
	LPCTSTR lpsz2;
};

#define ComboBox_AddFilter(hwndCtl, lpszCaption, lpszKey)       ((int)(DWORD)SNDMSG((hwndCtl), CB_ADD_FILTER, (WPARAM)(LPCTSTR)(lpszCaption), (LPARAM)(LPCTSTR)(lpszKey)))
#define ComboBox_AddFilterChoice(hwndCtl, filterIndex, lpszCaption, lpszKey)\
{\
	COMBOBOX_STRING_PAIR xTempVal(lpszCaption, lpszKey); \
	((int)(DWORD)SNDMSG((hwndCtl), CB_ADD_FILTER_CHOICE, (WPARAM)(int)(filterIndex), (LPARAM)(COMBOBOX_STRING_PAIR*)(&xTempVal))); \
}

#define ComboBox_SetFilterMultiSelection(hwndCtl, filterIdx, multiSelection)       ((int)(DWORD)SNDMSG((hwndCtl), CB_SET_FILTER_MULTI_SELECTION, (WPARAM)(int)(filterIdx), (WPARAM)(BOOL)(multiSelection)))

#define ComboBox_SetStringTag(hwndCtl, index, lpszKey, lpszValue)\
{\
	COMBOBOX_STRING_PAIR xTempVal(lpszKey, lpszValue);\
    ((int)(DWORD)SNDMSG((hwndCtl), CB_SET_STRING_TAG, (WPARAM)(int)(index), (LPARAM)(COMBOBOX_STRING_PAIR*)(&xTempVal)));\
}
#define ComboBox_DeleteStringTag(hwndCtl, index, lpszKey)       (SNDMSG((hwndCtl), CB_DELETE_STRING_TAG, (WPARAM)(int)(index), (LPARAM)(LPCTSTR)(lpszKey), 0L))
#define ComboBox_SetFilterUIWidth(hwndCtl, width)       (SNDMSG((hwndCtl), CB_SET_FILTER_UI_WIDTH, (WPARAM)(int)(width), 0L))
#define ComboBox_ParseTabs(hwndCtl, parseTabs)       ((int)(DWORD)SNDMSG((hwndCtl), CB_PARSE_TABS, (WPARAM)(BOOL)(parseTabs), 0L))
#define ComboBox_CalculateAutoWidth(hwndCtl)       ((int)(DWORD)SNDMSG((hwndCtl), CB_CALCULATE_AUTO_WIDTH, 0L, 0L))

#define ComboBox_SetEmptyText(hwndCtl, lpszText)       ((int)(DWORD)SNDMSG((hwndCtl), CB_SET_EMPTY_TEXT, (WPARAM)(LPCTSTR)(lpszText),0L))
#define ComboBox_AutoResetFilters(hwndCtl, autoResetFilters)      ((int)(DWORD)SNDMSG((hwndCtl), CB_AUTO_RESET_FILTERS, (WPARAM)(BOOL)(autoResetFilters), 0L))
#define ComboBox_DeleteAllFilters(hwndCtl)       ((int)(DWORD)SNDMSG((hwndCtl), CB_DELETE_ALL_FILTERS, 0L, 0L))
