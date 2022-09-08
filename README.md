# FilteredComboBoxControl
```
Full source code coming soon!
```

[Download Sample Executable From Here](https://github.com/huxia1124/FilteredComboBoxControl/raw/master/bin/FilteredComboBoxControl.exe)

Don't forget to [download 32-bit DLL file (Unicode)](https://github.com/huxia1124/FilteredComboBoxControl/raw/master/bin/FilteredComboBox.dll) or [download 64-bit DLL file (Unicode)](https://github.com/huxia1124/FilteredComboBoxControl/raw/master/bin/FilteredComboBox_x64.dll) too.

## A standard combo box with extension features such as instant filters and secondary item text.

- Implemented in pure Windows API.
- Easy to use. Just load the DLL and you have a new class "FilteredComboBox" ready to use
- Self-contained. No neeed to forward notifications from parent window
- Powerful. Supports multiple filters with an extra substring filter, highlighted.
- Built on standard "ComboBox" control. It sends all standard CBN_XXX notifications

Current Limitations: Works only in drop-down list mode.  CBS_SORT is not supported and you need to sort the data by yourself before adding them into the combobox.



![screenshot](https://github.com/huxia1124/FilteredComboBoxControl/blob/master/FilteredComboBoxControl/FilteredComboBox.gif)


## Usage:
```c++

    const int numFields = 4;
    const TCHAR* country_data[] =
    {
    _T("Angola"), _T("Africa"),_T("Middle Africa"),_T("(Other)"),
    //... list of all countries
    _T("Venezuela"), _T("South America"),_T("South America"),_T("(Other)")
    };

	// Just an ordinary main window as parent of combobox. You can put the combobox in any parent window.
	MainWindow w;
	w.Create(_T("Filtered Combobox Test"), 600, 400);
	w.Show();

#ifdef _M_X64
	LPCTSTR dllPath = _T("FilteredComboBox_x64.dll");
#else
	LPCTSTR dllPath = _T("FilteredComboBox.dll");
#endif

	HINSTANCE hDLL = LoadLibrary(dllPath);  // FilteredComboBox class is registered if dll is loaded successfully

	if (!hDLL)
	{
		TCHAR msg[200];
		_stprintf_s(msg, _T("Unable to load %s"), dllPath);
		MessageBox(nullptr, msg, _T("Error"), MB_OK | MB_ICONERROR);
		return 1;
	}

	// Now we can create the control using "FilteredComboBox" as class name
	HWND hWndCombo = CreateWindow(_T("FilteredComboBox"), _T(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | WS_VSCROLL, 20, 60, 300, 80, w.GetHWnd(), (HMENU)1322, nullptr, nullptr);
	if (!hWndCombo)
	{
		FreeLibrary(hDLL);
		return 0;
	}

	// Use default GUI font
	HFONT hFont = GetStockFont(DEFAULT_GUI_FONT);
	SendMessage(hWndCombo, WM_SETFONT, (WPARAM)hFont, 0);

	// FilteredComboBox has new messages to change filter settings. See FilteredComboBox.h
	ComboBox_ParseTabs(hWndCombo, true);


	int index = -1;

	// Sort the data by county names. We don't sort the original data set but store sorted indices.
	vector<int> indices(sizeof(country_data) / sizeof(country_data[0]) / numFields);
	iota(begin(indices), end(indices), 0);
	sort(begin(indices), end(indices), [](int a, int b)
		{
			return _tcscmp(country_data[a * numFields], country_data[b * numFields]) < 0;
		});

	// Collect the distinct continents/UN regions/level 1 types, for building filter options later.
	set<STLSTRING> allContinents;
	set<STLSTRING> allUnRegions;
	set<STLSTRING> allLevel1Types;

	STLSTRING text;
	for (int i = 0; i < sizeof(country_data) / sizeof(country_data[0]); i += numFields)
	{
		int idx = indices[i / numFields];

		text = country_data[idx * numFields];
		text += _T("\t");
		text += country_data[idx * numFields + 1];

		// Add combo items and attach tags to them. Filters will look for the tags.
		index = ComboBox_AddString(hWndCombo, text.c_str());
		ComboBox_SetStringTag(hWndCombo, index, _T("continent"), country_data[idx * numFields + 1]);
		ComboBox_SetStringTag(hWndCombo, index, _T("unregion"), country_data[idx * numFields + 2]);
		ComboBox_SetStringTag(hWndCombo, index, _T("level1type"), country_data[idx * numFields + 3]);

		// Collect the distinct continents/UN regions/level 1 types, for building filter options later.
		allContinents.insert(country_data[idx * numFields + 1]);
		allUnRegions.insert(country_data[idx * numFields + 2]);
		allLevel1Types.insert(country_data[idx * numFields + 3]);
	}

	// Now build the filters
	int idxFilter = ComboBox_AddFilter(hWndCombo, _T("Continent"), _T("continent"));
	ComboBox_SetFilterMultiSelection(hWndCombo, idxFilter, true);
	for (auto it = allContinents.begin(); it != allContinents.end(); ++it)
	{
		ComboBox_AddFilterChoice(hWndCombo, idxFilter, (*it).c_str(), (*it).c_str());
	}

	idxFilter = ComboBox_AddFilter(hWndCombo, _T("UN Region"), _T("unregion"));
	ComboBox_SetFilterMultiSelection(hWndCombo, idxFilter, true);
	for (auto it = allUnRegions.begin(); it != allUnRegions.end(); ++it)
	{
		ComboBox_AddFilterChoice(hWndCombo, idxFilter, (*it).c_str(), (*it).c_str());
	}

	idxFilter = ComboBox_AddFilter(hWndCombo, _T("Level 1 Type"), _T("level1type"));
	for (auto it = allLevel1Types.begin(); it != allLevel1Types.end(); ++it)
	{
		ComboBox_AddFilterChoice(hWndCombo, idxFilter, (*it).c_str(), (*it).c_str());
	}

	// Automatically adjust the width of drop-down list
	ComboBox_CalculateAutoWidth(hWndCombo);

	w.RunMessageLoop();

	FreeLibrary(hDLL);
```
