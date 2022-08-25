# FilteredComboBoxControl
```
Full source code coming soon!
```

[Download Sample Binary From Here](https://github.com/huxia1124/FilteredComboBoxControl/raw/master/bin/FilteredComboBoxSample.exe)

## A standard combo box with extension features such as instant filters and secondary item text.

![screenshot](https://github.com/huxia1124/FilteredComboBoxControl/blob/master/FilteredComboBoxControl/FilteredComboBox.gif)


## Usage:
```c++
    const int numFields = 4;
    const TCHAR* country_data[] =
    {
    _T("Angola"), _T("Africa"),_T("Middle Africa"),_T("(Other)"),
    //...
    };

    BufferedPaintInit();

    MainWindow w;
    w.Create(_T("Filtered Combobox Test"), 600, 400);
    w.Show();

    HFONT hFont = GetStockFont(DEFAULT_GUI_FONT);
    HWND hWndCombo = CreateWindow(_T("ComboBox"), _T(""), WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | WS_VSCROLL, 20, 20, 300, 80, w.GetHWnd(), nullptr, nullptr, nullptr);
    SendMessage(hWndCombo, WM_SETFONT, (WPARAM)hFont, 0);

    FilteredComboBox combo;
    combo.Attach(hWndCombo);
    w.ForwardNotification(&combo);
    w.ForwardDrawItem(&combo);

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
        combo.SetStringTag(index, _T("continent"), country_data[idx * numFields + 1]);
        combo.SetStringTag(index, _T("unregion"), country_data[idx * numFields + 2]);
        combo.SetStringTag(index, _T("level1type"), country_data[idx * numFields + 3]);

        allContinents.insert(country_data[idx * numFields + 1]);
        allUnRegions.insert(country_data[idx * numFields + 2]);
        allLevel1Types.insert(country_data[idx * numFields + 3]);
    }

    int idxFilter = combo.AddFilter(_T("Continent"), _T("continent"), true);
    FilteredComboBox::ComboFilterItemList* pFilterItemListContinent = combo.GetFilterItemList(idxFilter);
    for (auto it = allContinents.begin(); it != allContinents.end(); ++it)
    {
        pFilterItemListContinent->emplace_back(*it, *it);
    }

    idxFilter = combo.AddFilter(_T("UN Region"), _T("unregion"), true);
    FilteredComboBox::ComboFilterItemList* pFilterItemListUnRegion = combo.GetFilterItemList(idxFilter);
    for (auto it = allUnRegions.begin(); it != allUnRegions.end(); ++it)
    {
        pFilterItemListUnRegion->emplace_back(*it, *it);
    }

    idxFilter = combo.AddFilter(_T("Level 1 Type"), _T("level1type"), false);
    FilteredComboBox::ComboFilterItemList* pFilterItemListL1Type = combo.GetFilterItemList(idxFilter);
    for (auto it = allLevel1Types.begin(); it != allLevel1Types.end(); ++it)
    {
        pFilterItemListL1Type->emplace_back(*it, *it);
    }

    combo.BuildFilterUI();
    w.RunMessageLoop();
    BufferedPaintUnInit();
```
