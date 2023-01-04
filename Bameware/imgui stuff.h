#include <iostream>
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include "imgui/imgui_internal.h"

#define D3DDEV9_LEN 119

typedef HRESULT(__stdcall* EndScene_t)(LPDIRECT3DDEVICE9);
typedef LRESULT(CALLBACK* WndProc_t) (HWND, UINT, WPARAM, LPARAM);

//namespace Base
//{
//	bool Init();
//	bool Shutdown();
//	bool Detach();
//
//	namespace Data
//	{
//		extern HMODULE           hModule;
//		extern LPDIRECT3DDEVICE9 pDxDevice9;
//		extern void* pDeviceTable[D3DDEV9_LEN];
//		extern HWND              hWindow;
//		extern EndScene_t        oEndScene;
//		extern WndProc_t         oWndProc;
//		extern UINT              WmKeys[0xFF];
//		extern bool              Detached;
//		extern bool              ToDetach;
//		extern bool              InitImGui;
//		extern bool              ShowMenu;
//
//		namespace Keys
//		{
//			const UINT ToggleMenu = VK_INSERT;
//			const UINT DetachDll = VK_END;
//		}
//	}
//
//	namespace Hooks
//	{
//		bool Init();
//		bool Shutdown();
//		HRESULT __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice);
//		LRESULT CALLBACK  WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//	}
//}