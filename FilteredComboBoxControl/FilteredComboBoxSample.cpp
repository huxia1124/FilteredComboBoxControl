// FilteredComboBoxSample.cpp : Defines the entry point for the application.
//

#include "framework.h"

#include "MainWindow.h"
#include "FilteredComboBox.h"
#include <windowsx.h>
#include <numeric>
#include <random>
#include <set>
#include <vector>

using namespace std;

#ifdef UNICODE
typedef std::wstring STLSTRING;
#else
typedef std::string STLSTRING;
#endif

const int numFields = 4;
const TCHAR* country_data[] =
{
_T("Angola"), _T("Africa"),_T("Middle Africa"),_T("(Other)"),
_T("Burundi"), _T("Africa"),_T("Eastern Africa"),_T("Province"),
_T("Benin"), _T("Africa"),_T("Western Africa"),_T("Province"),
_T("Burkina Faso"), _T("Africa"),_T("Western Africa"),_T("Province"),
_T("Botswana"), _T("Africa"),_T("Southern Africa"),_T("(Other)"),
_T("Central African Republic"), _T("Africa"),_T("Middle Africa"),_T("(Other)"),
_T("Ivory Coast"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Cameroon"), _T("Africa"),_T("Middle Africa"),_T("Province"),
_T("Congo"), _T("Africa"),_T("Middle Africa"),_T("(Other)"),
_T("Comoros"), _T("Africa"),_T("Eastern Africa"),_T("(Other)"),
_T("Cape Verde"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Djibouti"), _T("Africa"),_T("Eastern Africa"),_T("District"),
_T("Algeria"), _T("Africa"),_T("Northern Africa"),_T("(Other)"),
_T("Egypt"), _T("Africa"),_T("Northern Africa"),_T("(Other)"),
_T("Eritrea"), _T("Africa"),_T("Eastern Africa"),_T("(Other)"),
_T("Ethiopia"), _T("Africa"),_T("Eastern Africa"),_T("(Other)"),
_T("Gabon"), _T("Africa"),_T("Middle Africa"),_T("Province"),
_T("Ghana"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Guinea"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Gambia"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Guinea-Bissau"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Equatorial Guinea"), _T("Africa"),_T("Middle Africa"),_T("(Other)"),
_T("Kenya"), _T("Africa"),_T("Eastern Africa"),_T("Province"),
_T("Liberia"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Libyan Arab Jamahiriya"), _T("Africa"),_T("Northern Africa"),_T("(Other)"),
_T("Lesotho"), _T("Africa"),_T("Southern Africa"),_T("District"),
_T("Morocco (includes Western Sahara)"), _T("Africa"),_T("Northern Africa"),_T("Province"),
_T("Madagascar"), _T("Africa"),_T("Eastern Africa"),_T("(Other)"),
_T("Mali"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Mozambique"), _T("Africa"),_T("Eastern Africa"),_T("Province"),
_T("Mauritania"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Mauritius"), _T("Africa"),_T("Eastern Africa"),_T("(Other)"),
_T("Malawi"), _T("Africa"),_T("Eastern Africa"),_T("District"),
_T("Mayotte"), _T("Africa"),_T("(Unknown)"),_T("(Other)"),
_T("Namibia"), _T("Africa"),_T("Southern Africa"),_T("(Other)"),
_T("Niger"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Nigeria"), _T("Africa"),_T("Western Africa"),_T("State"),
_T("Reunion"), _T("Africa"),_T("Eastern Africa"),_T("(Other)"),
_T("Rwanda"), _T("Africa"),_T("Eastern Africa"),_T("(Other)"),
_T("Sudan"), _T("Africa"),_T("Northern Africa"),_T("State"),
_T("Senegal"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("St. Helena"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Sierra Leone"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Somalia"), _T("Africa"),_T("Eastern Africa"),_T("(Other)"),
_T("Sao Tome and Principe"), _T("Africa"),_T("Middle Africa"),_T("(Other)"),
_T("Swaziland"), _T("Africa"),_T("Southern Africa"),_T("(Other)"),
_T("Seychelles"), _T("Africa"),_T("Eastern Africa"),_T("District"),
_T("Chad"), _T("Africa"),_T("Middle Africa"),_T("(Other)"),
_T("Togo"), _T("Africa"),_T("Western Africa"),_T("(Other)"),
_T("Tunisia"), _T("Africa"),_T("Northern Africa"),_T("(Other)"),
_T("United Rep. of Tanzania"), _T("Africa"),_T("Eastern Africa"),_T("(Other)"),
_T("Uganda"), _T("Africa"),_T("Eastern Africa"),_T("District"),
_T("South Africa"), _T("Africa"),_T("Southern Africa"),_T("Province"),
_T("Zambia"), _T("Africa"),_T("Eastern Africa"),_T("Province"),
_T("Zimbabwe"), _T("Africa"),_T("Eastern Africa"),_T("Province"),
_T("Afghanistan"), _T("Asia"),_T("South-central Asia"),_T("Province"),
_T("United Arab Emirates"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Armenia"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Azerbaijan"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Bangladesh"), _T("Asia"),_T("South-central Asia"),_T("(Other)"),
_T("Bahrain"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Brunei Darussalam"), _T("Asia"),_T("South-eastern Asia"),_T("District"),
_T("Bhutan"), _T("Asia"),_T("South-central Asia"),_T("District"),
_T("China"), _T("Asia"),_T("Eastern Asia"),_T("Province"),
_T("Cyprus"), _T("Asia"),_T("Western Asia"),_T("District"),
_T("Georgia"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Hong Kong"), _T("Asia"),_T("Eastern Asia"),_T("District"),
_T("Indonesia"), _T("Asia"),_T("South-eastern Asia"),_T("(Other)"),
_T("India"), _T("Asia"),_T("South-central Asia"),_T("State"),
_T("Iran"), _T("Asia"),_T("South-central Asia"),_T("(Other)"),
_T("Iraq"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Israel"), _T("Asia"),_T("Western Asia"),_T("District"),
_T("Jordan"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Japan"), _T("Asia"),_T("Eastern Asia"),_T("(Other)"),
_T("Kazakhstan"), _T("Asia"),_T("South-central Asia"),_T("(Other)"),
_T("Kyrgyz Republic"), _T("Asia"),_T("South-central Asia"),_T("(Other)"),
_T("Cambodia"), _T("Asia"),_T("South-eastern Asia"),_T("Province"),
_T("Korea"), _T("Asia"),_T("Eastern Asia"),_T("Province"),
_T("Kuwait"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Lao People's Democratic Republic"), _T("Asia"),_T("South-eastern Asia"),_T("Province"),
_T("Lebanon"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Sri Lanka"), _T("Asia"),_T("South-central Asia"),_T("Province"),
_T("Macao"), _T("Asia"),_T("Eastern Asia"),_T("(Other)"),
_T("Maldives"), _T("Asia"),_T("South-central Asia"),_T("(Other)"),
_T("Myanmar"), _T("Asia"),_T("South-eastern Asia"),_T("State"),
_T("Mongolia"), _T("Asia"),_T("Eastern Asia"),_T("(Other)"),
_T("Malaysia"), _T("Asia"),_T("South-eastern Asia"),_T("State"),
_T("Nepal"), _T("Asia"),_T("South-central Asia"),_T("(Other)"),
_T("Oman"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Pakistan"), _T("Asia"),_T("South-central Asia"),_T("Province"),
_T("Philippines"), _T("Asia"),_T("South-eastern Asia"),_T("(Other)"),
_T("Occupied Palestinian Territory"), _T("Asia"),_T("(Unknown)"),_T("District"),
_T("Qatar"), _T("Asia"),_T("Western Asia"),_T("District"),
_T("Saudi Arabia"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Singapore"), _T("Asia"),_T("South-eastern Asia"),_T("(Other)"),
_T("Syrian Arab Republic"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Thailand"), _T("Asia"),_T("South-eastern Asia"),_T("Province"),
_T("Tajikistan"), _T("Asia"),_T("South-central Asia"),_T("(Other)"),
_T("Turkmenistan"), _T("Asia"),_T("South-central Asia"),_T("(Other)"),
_T("East Timor"), _T("Asia"),_T("South-eastern Asia"),_T("(Other)"),
_T("Turkey"), _T("Asia"),_T("Western Asia"),_T("Province"),
_T("Taiwan"), _T("Asia"),_T("(Unknown)"),_T("(Other)"),
_T("Uzbekistan"), _T("Asia"),_T("South-central Asia"),_T("(Other)"),
_T("Viet Nam"), _T("Asia"),_T("South-eastern Asia"),_T("Province"),
_T("Yemen"), _T("Asia"),_T("Western Asia"),_T("(Other)"),
_T("Albania"), _T("Europe"),_T("Southern Europe"),_T("District"),
_T("Andorra"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Austria"), _T("Europe"),_T("Western Europe"),_T("State"),
_T("Belgium"), _T("Europe"),_T("Western Europe"),_T("Province"),
_T("Bulgaria"), _T("Europe"),_T("Eastern Europe"),_T("(Other)"),
_T("Bosnia-Herzogovina"), _T("Europe"),_T("Southern Europe"),_T("District"),
_T("Belarus"), _T("Europe"),_T("Eastern Europe"),_T("(Other)"),
_T("Switzerland"), _T("Europe"),_T("Western Europe"),_T("(Other)"),
_T("Czech Republic"), _T("Europe"),_T("Eastern Europe"),_T("(Other)"),
_T("Germany"), _T("Europe"),_T("Western Europe"),_T("(Other)"),
_T("Denmark"), _T("Europe"),_T("Northern Europe"),_T("(Other)"),
_T("Spain"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Estonia"), _T("Europe"),_T("Northern Europe"),_T("(Other)"),
_T("Finland"), _T("Europe"),_T("Northern Europe"),_T("(Other)"),
_T("France"), _T("Europe"),_T("Western Europe"),_T("(Other)"),
_T("Faeroe Islands"), _T("Europe"),_T("Northern Europe"),_T("(Other)"),
_T("United Kingdom"), _T("Europe"),_T("Northern Europe"),_T("(Other)"),
_T("Guernsey"), _T("Europe"),_T("(Unknown)"),_T("(Other)"),
_T("Gibraltar"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Greece"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Croatia"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Hungary"), _T("Europe"),_T("Eastern Europe"),_T("(Other)"),
_T("Isle of Man"), _T("Europe"),_T("(Unknown)"),_T("(Other)"),
_T("Iceland"), _T("Europe"),_T("Northern Europe"),_T("(Other)"),
_T("Italy"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Jersey"), _T("Europe"),_T("(Unknown)"),_T("(Other)"),
_T("Liechtenstein"), _T("Europe"),_T("Western Europe"),_T("(Other)"),
_T("Lithuania"), _T("Europe"),_T("Northern Europe"),_T("Province"),
_T("Luxembourg"), _T("Europe"),_T("Western Europe"),_T("(Other)"),
_T("Latvia"), _T("Europe"),_T("Northern Europe"),_T("(Other)"),
_T("Monaco"), _T("Europe"),_T("Western Europe"),_T("(Other)"),
_T("Republic of Moldova"), _T("Europe"),_T("Eastern Europe"),_T("(Other)"),
_T("Macedonia"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Malta"), _T("Europe"),_T("Southern Europe"),_T("District"),
_T("Netherlands"), _T("Europe"),_T("Western Europe"),_T("Province"),
_T("Norway"), _T("Europe"),_T("Northern Europe"),_T("(Other)"),
_T("Portugal"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Romania"), _T("Europe"),_T("Eastern Europe"),_T("(Other)"),
_T("Russia"), _T("Europe"),_T("Eastern Europe"),_T("(Other)"),
_T("Serbia and Montenegro"), _T("Europe"),_T("Southern Europe"),_T("Province"),
_T("Svalbard"), _T("Europe"),_T("(Unknown)"),_T("(Other)"),
_T("San Marino"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Slovakia"), _T("Europe"),_T("Eastern Europe"),_T("(Other)"),
_T("Slovenia"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Sweden"), _T("Europe"),_T("Northern Europe"),_T("(Other)"),
_T("Ukraine"), _T("Europe"),_T("Eastern Europe"),_T("(Other)"),
_T("Holy See"), _T("Europe"),_T("Southern Europe"),_T("(Other)"),
_T("Ireland"), _T("Europe"),_T("Northern Europe"),_T("Province"),
_T("Poland"), _T("Europe"),_T("Eastern Europe"),_T("(Other)"),
_T("Aruba"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Anguilla"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Netherland Antilles"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Antigua and Barbuda"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Bahamas"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Belize"), _T("North America"),_T("Central America"),_T("District"),
_T("Bermuda"), _T("North America"),_T("Northern America"),_T("(Other)"),
_T("Barbados"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Canada"), _T("North America"),_T("Northern America"),_T("Province"),
_T("Costa Rica"), _T("North America"),_T("Central America"),_T("(Other)"),
_T("Cuba"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Cayman Islands"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Commonwealth of Dominica"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Dominican Republic"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Guadeloupe"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Grenada"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Greenland"), _T("North America"),_T("Northern America"),_T("(Other)"),
_T("Guatemala"), _T("North America"),_T("Central America"),_T("(Other)"),
_T("Honduras"), _T("North America"),_T("Central America"),_T("(Other)"),
_T("Haiti"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Jamaica"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Saint Kitts and Nevis"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Saint Lucia"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Mexico"), _T("North America"),_T("Central America"),_T("(Other)"),
_T("Montserrat"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Martinique"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Nicaragua"), _T("North America"),_T("Central America"),_T("(Other)"),
_T("Panama"), _T("North America"),_T("Central America"),_T("(Other)"),
_T("Puerto Rico"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("El Salvador"), _T("North America"),_T("Central America"),_T("(Other)"),
_T("St-Pierre and Miquelon"), _T("North America"),_T("Northern America"),_T("(Other)"),
_T("Turks and Caicos Islands"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("Trinidad and Tobago"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("United States of America"), _T("North America"),_T("Northern America"),_T("State"),
_T("St. Vincent"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("British Virgin Islands"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("United States Virgin Islands"), _T("North America"),_T("Caribbean"),_T("(Other)"),
_T("American Samoa"), _T("Oceania"),_T("Polynesia"),_T("(Other)"),
_T("Australia"), _T("Oceania"),_T("Australia and New Zealand"),_T("State"),
_T("Cook Islands"), _T("Oceania"),_T("Polynesia"),_T("(Other)"),
_T("Fiji"), _T("Oceania"),_T("Melanesia"),_T("Province"),
_T("Federated State of Micronesia"), _T("Oceania"),_T("Micronesia"),_T("(Other)"),
_T("Guam"), _T("Oceania"),_T("Micronesia"),_T("(Other)"),
_T("Kiribati"), _T("Oceania"),_T("Micronesia"),_T("(Other)"),
_T("Marshall Islands"), _T("Oceania"),_T("Micronesia"),_T("(Other)"),
_T("Northern Mariana Islands"), _T("Oceania"),_T("Micronesia"),_T("(Other)"),
_T("New Caledonia"), _T("Oceania"),_T("Melanesia"),_T("Province"),
_T("Niue"), _T("Oceania"),_T("Polynesia"),_T("(Other)"),
_T("Nauru"), _T("Oceania"),_T("Micronesia"),_T("(Other)"),
_T("New Zealand"), _T("Oceania"),_T("Australia and New Zealand"),_T("(Other)"),
_T("Pitcairn"), _T("Oceania"),_T("Polynesia"),_T("(Other)"),
_T("Palau"), _T("Oceania"),_T("Micronesia"),_T("State"),
_T("Papua New Guinea"), _T("Oceania"),_T("Melanesia"),_T("Province"),
_T("French Polynesia"), _T("Oceania"),_T("Polynesia"),_T("(Other)"),
_T("Solomon Islands"), _T("Oceania"),_T("Melanesia"),_T("Province"),
_T("Tonga"), _T("Oceania"),_T("Polynesia"),_T("(Other)"),
_T("Tuvalu"), _T("Oceania"),_T("Polynesia"),_T("(Other)"),
_T("Vanuatu"), _T("Oceania"),_T("Melanesia"),_T("Province"),
_T("Wallis and Futuna"), _T("Oceania"),_T("Polynesia"),_T("(Other)"),
_T("Western Samoa"), _T("Oceania"),_T("Polynesia"),_T("(Other)"),
_T("Argentina"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Bolivia"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Brazil"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Chile"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Colombia"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Ecuador"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Falkland Islands"), _T("South America"),_T("South America"),_T("(Other)"),
_T("French Guiana"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Guyana"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Peru"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Paraguay"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Suriname"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Uruguay"), _T("South America"),_T("South America"),_T("(Other)"),
_T("Venezuela"), _T("South America"),_T("South America"),_T("(Other)")
};

#define COMBOBOX_CONTROL_ID		1322
class MyMainWindow : public MainWindow
{
public:
	HWND m_hWndLabel;

	virtual void PostWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override
	{
		if (message == WM_CREATE)
		{
			// Create a label to show currect selection
			m_hWndLabel = CreateWindow(_T("Static"), _T(""), WS_CHILD | WS_VISIBLE, 20, 100, 400, 20, hWnd, (HMENU)1601, nullptr, nullptr);
		}
		else if (message == WM_COMMAND && (HIWORD(wParam) == CBN_SELENDOK))
		{
			// CBN_SELENDOK handler

			TCHAR szText[500];
			HWND m_hWndCombo = reinterpret_cast<HWND>(lParam);
			int sel = ComboBox_GetCurSel(m_hWndCombo);
			ComboBox_GetLBText(m_hWndCombo, sel, szText);
			SetWindowText(m_hWndLabel, szText);
		}
	}
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Just an ordinary main window as parent of combobox. You can put the combobox in any parent window.
	MyMainWindow w;
	w.Create(_T("Filtered Combobox Test"), 800, 600);
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
	HWND hWndCombo = CreateWindow(_T("FilteredComboBox"), _T(""), WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST | CBS_OWNERDRAWFIXED | CBS_HASSTRINGS | WS_VSCROLL, 20, 60, 300, 80, w.GetHWnd(), (HMENU)COMBOBOX_CONTROL_ID, nullptr, nullptr);
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
	ComboBox_SetEmptyText(hWndCombo, _T("<Unknown>"));


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

	return 0;
}