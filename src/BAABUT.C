#define WIN31
#include <windows.h>
#include <string.h>

#define PICS	30
#define SPEED	2
#define DELAYTIME	40
#define PARETYVAL	5328

LONG FAR PASCAL WndProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInstance;
char szProgName[] = "Baabut";
char szAboutString[] = "Ba`abut\n\nProgramming:   Russlan Kefri\n\nHama - Syria - Tel: 033-237297\n";

int LastX = 0,LastY = 0;
int MouseX = 0,MouseY = 0;
int State = 0;
int Pic = 0,LastPic = 0;
int Counter = 0, Counter2 = 0;
int Sec = 0;

HBITMAP hCatBmp[PICS];

#pragma argsused

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpszCmdLine, int nCmdShow)
{

	HWND hWnd;
	MSG lpMsg;
	WNDCLASS wcApp;

	hInstance = hInst;

	if (!hPrevInst) {
		wcApp.lpszClassName = szProgName;
		wcApp.hInstance = hInstance;
		wcApp.lpfnWndProc = WndProc;
		wcApp.hCursor = LoadCursor(hInst,"CURSOR_1");
		wcApp.hIcon = NULL;// LoadIcon(hInst,"AppIcon");
		wcApp.lpszMenuName = "APPMENU";
		wcApp.hbrBackground = GetStockObject(WHITE_BRUSH);
		wcApp.style = CS_HREDRAW | CS_VREDRAW;
		wcApp.cbClsExtra = 0;
		wcApp.cbWndExtra = 0;

		if (!RegisterClass(&wcApp))
			return FALSE;
	}


	hWnd = CreateWindow(szProgName, "Ba`abut", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, (HWND)NULL, (HWND)NULL, (HANDLE)hInst, (LPSTR)NULL);
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

	hCatBmp[0] = LoadBitmap(hInstance, "a1001");
	hCatBmp[1] = LoadBitmap(hInstance, "a1002");
	hCatBmp[2] = LoadBitmap(hInstance, "a1003");
	hCatBmp[3] = LoadBitmap(hInstance, "a1004");
	hCatBmp[4] = LoadBitmap(hInstance, "a1005");
	hCatBmp[5] = LoadBitmap(hInstance, "a1006");
	hCatBmp[6] = LoadBitmap(hInstance, "a1007");
	hCatBmp[7] = LoadBitmap(hInstance, "a1008");

	hCatBmp[8] = LoadBitmap(hInstance, "b1001");
	hCatBmp[9] = LoadBitmap(hInstance, "b1002");
	hCatBmp[10] = LoadBitmap(hInstance, "b1003");
	hCatBmp[11] = LoadBitmap(hInstance, "b1004");
	hCatBmp[12] = LoadBitmap(hInstance, "b1005");
	hCatBmp[13] = LoadBitmap(hInstance, "b1006");
	hCatBmp[14] = LoadBitmap(hInstance, "b1007");
	hCatBmp[15] = LoadBitmap(hInstance, "b1008");

	hCatBmp[16] = LoadBitmap(hInstance, "c1001");
	hCatBmp[17] = LoadBitmap(hInstance, "c1002");
	hCatBmp[18] = LoadBitmap(hInstance, "c1003");
	hCatBmp[19] = LoadBitmap(hInstance, "c1004");
	hCatBmp[20] = LoadBitmap(hInstance, "c1005");
	hCatBmp[21] = LoadBitmap(hInstance, "c1006");
	hCatBmp[22] = LoadBitmap(hInstance, "c1007");

	hCatBmp[23] = LoadBitmap(hInstance, "d1001");
	hCatBmp[24] = LoadBitmap(hInstance, "d1002");
	hCatBmp[25] = LoadBitmap(hInstance, "d1003");
	hCatBmp[26] = LoadBitmap(hInstance, "d1004");
	hCatBmp[27] = LoadBitmap(hInstance, "d1005");
	hCatBmp[28] = LoadBitmap(hInstance, "d1006");
	hCatBmp[29] = LoadBitmap(hInstance, "d1007");
	hCatBmp[30] = LoadBitmap(hInstance, "d1008");
	hCatBmp[31] = LoadBitmap(hInstance, "d1009");
	SetTimer(hWnd,1,DELAYTIME,NULL);
	
	while (GetMessage(&lpMsg, NULL, NULL, NULL)) {
		TranslateMessage(&lpMsg);
		DispatchMessage(&lpMsg);
	}
	return (lpMsg.wParam);
}

void DisplayPic(HWND hWnd, int X, int Y, int PicNo)
{
	HDC hDC, hMemDC;
	HBITMAP hOldBitmap;

	hDC = GetDC(hWnd);
	hMemDC = CreateCompatibleDC(hDC);
	hOldBitmap = SelectObject(hMemDC,hCatBmp[PicNo]);
	BitBlt(hDC, X, Y, 64, 64, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC,hOldBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd,hDC);

    LastPic = PicNo;
}
 
void ExitApp(HWND hWnd)
{
    int i;
	KillTimer(hWnd,1);
	for (i = 0;i <= 31;i ++) DeleteObject(hCatBmp[i]);
	PostQuitMessage(0);
}

int TestParety(HWND hWnd)
{
	int Parety = 0;
	int i,l;
    // char Buf[100];

	l = _fstrlen(szAboutString);
	for( i = 0; i < l; i ++)
		Parety += szAboutString[i];

	// wsprintf(Buf,"Parety value = [%d]",Parety);
	// MessageBox(hWnd,Buf,"Parety Value",MB_OK);
	return (Parety == PARETYVAL);
}

BOOL CALLBACK AboutDialogProc(HWND hDlg, UINT Message, WPARAM wParam, LPARAM lParam)
{

	switch (Message) {
	case WM_INITDIALOG:
    	SetDlgItemText(hDlg, 101, szAboutString);
		return TRUE;

	case WM_COMMAND:
		switch (wParam) {
		case 1:
			EndDialog(hDlg, TRUE);
			return TRUE;
		default:
			return FALSE;
		}
		break;
	default:
		return FALSE;
	}; 
	return FALSE;
}

BOOL fDialog (LPSTR lpszResName, HWND hwnd, FARPROC fpfn)
{
    BOOL        f;
    HANDLE      hInst;

    hInst = GetWindowWord (hwnd, GWW_HINSTANCE);
    fpfn  = MakeProcInstance (fpfn, hInst);
	f = DialogBox (hInst, lpszResName, hwnd, fpfn);
    FreeProcInstance (fpfn);
    return f;
}

void PaintWindow(HWND hWnd)
{
	HDC hDC, hMemDC;
	HBITMAP hOldBitmap;
    PAINTSTRUCT Ps;

	hDC = BeginPaint(hWnd,&Ps);
	hMemDC = CreateCompatibleDC(hDC);
	hOldBitmap = SelectObject(hMemDC,hCatBmp[LastPic]);
	BitBlt(hDC, LastX, LastY, 64, 64, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC,hOldBitmap);
	DeleteDC(hMemDC);
	EndPaint(hWnd,&Ps);
}

LONG FAR PASCAL WndProc(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam)
{
	int NewX, NewY, i;

	switch (messg)
	{
	 case WM_PAINT:
        PaintWindow(hWnd);
     	break;
	 case WM_MOUSEMOVE:
		MouseX = LOWORD(lParam) - 32;
		MouseY = HIWORD(lParam) - 45;
		Counter2 = 0;
		break;
	 case WM_TIMER:
		switch (State) {
			case 0:
            	State = 4;
				Pic = 0;
				Counter = 0;
				LastX = MouseX;
				LastY = MouseY;
				break;
			case 1:
				if ((LastX != MouseX) || (LastY != MouseY)) {
					if (MouseX > (LastX + SPEED)) {
						NewX = LastX + SPEED;
						Sec = 0;
					}
					else if (MouseX < (LastX - SPEED)) {
						NewX = LastX - SPEED;
						Sec = 8;
					} else {
						NewX = MouseX;
            		}

					if (MouseY > (LastY + SPEED)) {
						NewY = LastY + SPEED;
					}
					else if (MouseY < (LastY - SPEED)) {
						NewY = LastY - SPEED;
					} else {
						NewY = MouseY;
            		}

					DisplayPic(hWnd, NewX, NewY, Pic + Sec);
					Pic = ((Pic + 1) % 8);

					LastX = NewX;
					LastY = NewY;

					if (Counter != 500) {
						Counter ++;
					}
					else {
						Counter = 0;
						Counter2 = 0;
                        Pic = 0;
                    	State = 6;
                    }
				} else {
					State = 2;
					Counter = 0; 
				}
				break;
			case 2:
				if ((LastX != MouseX) || (LastY != MouseY)) {
					State = 1;
					Pic = 0;
                    Counter = 0;
				} else {
					if (Counter < 100) {
						Counter ++;
						if (Counter == 1)
							DisplayPic(hWnd, LastX, LastY, 16);

					} else {
						Pic = 0;
						State = 3;
                        Counter = 0;
					} 
				}
				break;
			case 3:
				if ((LastX != MouseX) || (LastY != MouseY)) {
					State = 5;
                    Counter = 0;
				} else {
					if (Counter != 10) {
						Counter ++;
					}
					else if (Pic < 5) {
						Counter = 0;
						Pic ++;
						DisplayPic(hWnd, LastX, LastY, Pic + 16);
					}
					else {
						State = 4;
						Counter = 0;
						Pic = 0;
                    }
				}
				break;
			case 4:
				if ((LastX != MouseX) || (LastY != MouseY)) {
					State = 5;
					Counter = 0;
                    Pic = 5;
				} else {
					if (Counter == 20) {
						DisplayPic(hWnd, LastX, LastY, 22);
					}
					else if (Counter == 40) {
						DisplayPic(hWnd, LastX, LastY, 21);
					}
					else if (Counter == 100) {
						Counter = 0;
					};
					Counter ++;
				}
				break;
			case 5:
				if (Counter == 10) {
					if (Pic > 0) {
						Pic --;
						DisplayPic(hWnd, LastX, LastY, 16 + Pic);
					}
					else {
						State = 1;
						Counter = 0;
                        Pic = 0;
                    }
				}
                else { 
					Counter ++;
                }
				break;
			case 6:
				if (Counter == 3) {
					if (Pic > 8) {
						Pic = 4;
                        Counter2 ++;
					}
                    if (Counter2 < 4) {
						DisplayPic(hWnd, LastX, LastY, 23 + Pic);
                    	Pic ++;
						Counter = 0;
					}
					else {
						Counter2 = 0;
						Counter = 0;
						Pic = 0;
                        State = 1;
                    }
				}
				else {
                	Counter ++;
				}
				break;
            };
		break;
	 case WM_COMMAND:
		switch (wParam) {
			case 101:
				if (TestParety(hWnd))
					fDialog ("DIALOG_1", hWnd, (FARPROC)AboutDialogProc);
			break;
			case 102:
				ExitApp(hWnd);
            break;
        }
     	break;
	 case WM_SIZE:
		if (wParam == SIZE_MINIMIZED) {
			MouseX = - 10;
			MouseY = - 20;
			State = 1;
			Pic = 0;
            Counter = 0;
		}
        break;
	 case WM_DESTROY:
		ExitApp(hWnd);
 		break;
	 default:
		return DefWindowProc(hWnd, messg, wParam, lParam);
	 }
     return 0L;
} 