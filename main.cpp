#define UNICODE
#pragma comment(linker,"/opt:nowin98")
#include<windows.h>

TCHAR szClassName[]=TEXT("Window");

LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
	static HWND hEdit;
	switch(msg)
	{
	case WM_CREATE:
		hEdit=CreateWindowEx(WS_EX_CLIENTEDGE,TEXT("EDIT"),0,WS_VISIBLE|WS_CHILD,10,10,512,30,hWnd,0,((LPCREATESTRUCT)lParam)->hInstance,0);
		CreateWindow(TEXT("BUTTON"),TEXT("ゴミ箱に移動する"),WS_VISIBLE|WS_CHILD,532,10,150,30,hWnd,(HMENU)100,((LPCREATESTRUCT)lParam)->hInstance,0);
		break;
	case WM_COMMAND:
		if(wParam==100)
		{
			TCHAR szTemp[1024];
			ZeroMemory(szTemp,sizeof(TCHAR)*1024);//ファイルは複数登録可能、ファイルパスの間は'\0'で区切り最後のファイルパスの後ろには"\0\0"と\0を2つつける必要がある。
			if(0==GetWindowTextLength(hEdit))break;
			GetWindowText(hEdit,szTemp,1024);
			SHFILEOPSTRUCT fs;
			ZeroMemory(&fs,sizeof(SHFILEOPSTRUCT));
			fs.hwnd=hWnd;
			fs.wFunc=FO_DELETE;
			fs.pFrom=szTemp;
			fs.pTo=NULL;
			fs.fFlags=FOF_SILENT|FOF_NOCONFIRMATION|FOF_ALLOWUNDO;
			if(SHFileOperation(&fs)!=0)
				MessageBox(hWnd,TEXT("何らかのエラーで操作は完了しませんでした。"),0,0);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd,msg,wParam,lParam);
	}
	return 0;
}

EXTERN_C void __cdecl WinMainCRTStartup()
{
	MSG msg;
	HINSTANCE hInstance=GetModuleHandle(0);
	WNDCLASS wndclass={CS_HREDRAW|CS_VREDRAW,WndProc,0,0,hInstance,0,LoadCursor(0,IDC_ARROW),(HBRUSH)(COLOR_WINDOW+1),0,szClassName};
	RegisterClass(&wndclass);
	HWND hWnd=CreateWindow(szClassName,TEXT("Window"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,0,CW_USEDEFAULT,0,0,0,hInstance,0);
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ExitProcess(0);
}

#if _DEBUG
void main(){}
#endif