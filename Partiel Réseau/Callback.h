#pragma once
#include "utils.h"

class Callback
{
private:

public:
	LRESULT CALLBACK ServWinProc(HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam);
};