# FilteredComboBoxControl
```
Full source code coming soon!
```

[Download Sample Binary From Here](https://github.com/huxia1124/FilteredComboBoxControl/raw/master/bin/FilteredComboBoxSample.exe)

## A standard combo box with extension features such as instant filters and secondary item text.

![screenshot](https://github.com/huxia1124/FilteredComboBoxControl/blob/master/FilteredComboBoxControl/FilteredComboBox.gif)


## Usage:
```c++

class MyMainWindow : public MainWindow
{
public:
    MyMainWindow() : _comboBox(nullptr) {}
    void SetComboBox(HWND hWndComboBox) { _comboBox = hWndComboBox; }

protected:
    virtual LRESULT PreWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override
    {
        if (_comboBox)
        {
            FilteredComboBox::ForwardParentMessage(_comboBox, hWnd, message, wParam, lParam);
        }
        return 0;
    }

private:
    HWND _comboBox;
};


    const int numFields = 4;
    const TCHAR* country_data[] =
    {
    _T("Angola"), _T("Africa"),_T("Middle Africa"),_T("(Other)"),
    //...
    };

    BufferedPaintInit();

    MyMainWindow w;
    w.Create(_T("Filtered Combobox Test"), 600, 400);
    w.Show();

    FilteredComboBox::SuperclassComboBox(_T("FilteredComboBox"));
    HWND hWndCombo = CreateWindow(_T("FilteredComboBox"), _T(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | WS_VSCROLL, 20, 60, 300, 80, w.GetHWnd(), (HMENU)1322, nullptr, nullptr);
    if (!hWndCombo)
    {
        BufferedPaintUnInit();
        return 0;
    }

    w.SetComboBox(hWndCombo);

    ComboBox_ParseTabs(hWndCombo, true);

    HFONT hFont = GetStockFont(DEFAULT_GUI_FONT);
    SendMessage(hWndCombo, WM_SETFONT, (WPARAM)hFont, 0);

    int index = -1;

    vector<int> indices(sizeof(country_data) / sizeof(country_data[0]) / numFields);
    iota(begin(indices), end(indices), 0);
    sort(begin(indices), end(indices), [](int a, int b)
        {
            return _tcscmp(country_data[a * numFields], country_data[b * numFields]) < 0;
        });

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
        index = ComboBox_AddString(hWndCombo, text.c_str());
        ComboBox_SetStringTag(hWndCombo, index, _T("continent"), country_data[idx * numFields + 1]);
        ComboBox_SetStringTag(hWndCombo, index, _T("unregion"), country_data[idx * numFields + 2]);
        ComboBox_SetStringTag(hWndCombo, index, _T("level1type"), country_data[idx * numFields + 3]);

        allContinents.insert(country_data[idx * numFields + 1]);
        allUnRegions.insert(country_data[idx * numFields + 2]);
        allLevel1Types.insert(country_data[idx * numFields + 3]);
   }
   
    int idxFilter = ComboBox_AddFilter(hWndCombo, _T("Continent"), _T("continent"));
    ComboBox_SetFilterMultiSelection(hWndCombo, idxFilter, true);
    for (auto it = allContinents.begin(); it != allContinents.end(); ++it)
    {
        ComboBox_AddFilterChoice(hWndCombo, idxFilter , (*it).c_str(), (*it).c_str());
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

    ComboBox_CalculateAutoWidth(hWndCombo);
    w.RunMessageLoop();

    BufferedPaintUnInit();
```
