#include "includes.h"

#include "UTILS\interfaces.h"
#include "UTILS\hooks.h"
#include "UTILS\offsets.h"
#include "UTILS\NetvarManager.h"
#include "FEATURES\EventListeners.h"
#include "FEATURES\Misc.h"
#include "SDK\IEngine.h"
#include "UTILS\Debugger.h"
#include "UTILS\hooks.h"
#include <bass.h>
#include "dll.h"
#include <Windows.h>
#include "api.h"
#include "includes/sounds.h"
#include "../imgui stuff.h"
#include "../includes/detours.h"
#include <d3dx9.h>
#pragma comment(lib, "detours.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include "PPGUI Framework/PPGUI.h"
#include "PPGUI Framework/Menu.h"
#include "Header.h"
#include <FEATURES/Configurations.h>

HINSTANCE DllHandle;

typedef HRESULT(__stdcall* endScene)(IDirect3DDevice9* pDevice);
endScene pEndScene;

ImFont* font;

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WNDPROC oWndProc;
static HWND window = NULL;

void Start()
{
	AllocConsole();
	FILE* fasfasf;
	freopen_s(&fasfasf, "CONOUT$", "w+", stdout);
	
	printf("[~] chadhook\n");

	while (!GetModuleHandleA("serverbrowser.dll"))
		Sleep(200);

	INTERFACES::InitInterfaces();
	OFFSETS::InitOffsets();

	UTILS::INPUT::input_handler.Init();
	FONTS::InitFonts();

	HOOKS::InitHooks();
	HOOKS::InitNetvarHooks();
	FEATURES::MISC::InitializeEventListeners();

	FEATURES::MISC::LoadUserConfig();

	GLOBAL::cheat_start_time = GetTickCount() * 0.001f;

	//std::cout << "[+] 0x" << std::hex << GetProcAddress(GetModuleHandle("tier0.dll"), "Msg") << std::endl;
	printf("[~] welcome to chadhook!\n");

	const char* dwnld_URL = "https://cdn.discordapp.com/attachments/944745197575733279/1060015213002362940/sound.mp3";
	const char* savepath = "C:\\sound.mp3";
	URLDownloadToFile(NULL, dwnld_URL, savepath, 0, 0);
	//BASS::bass_lib_handle = BASS::bass_lib.LoadFromFile("C:\\bass.dll");
	//BASS_Init(-1, 44800, 0, 0, NULL);
	//DWORD handle2 = BASS_StreamCreateFile(false, savepath, 0, 0, BASS_SAMPLE_LOOP);
	//BASS_ChannelPlay(handle2, false);
	playback_loop();
	while (true) {
		BASS_SetVolume(BASS::open ? BASS::vol23 : 0);
		Sleep(200);
	}
	system("del C:\\sound.mp3");
}

void InitImGui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
	font = io.Fonts->AddFontFromFileTTF("C:\\museo.ttf", 13.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	SETTINGS::ragebot_configs.aimbot_ignore_head_type = 3;
}
bool init = false;

static int tabs;

int accent_color[4] = { 255, 41, 53, 255 };

static int tab = 0;
static int tab2 = 0;

HRESULT __stdcall hookedEndScene(IDirect3DDevice9* pDevice) {

	if (!init)
	{
		InitImGui(pDevice);
		init = true;

	}

	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImFontConfig font_config;
	font_config.OversampleH = 1; //or 2 is the same
	font_config.OversampleV = 1;
	font_config.PixelSnapH = 1;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x044F, // Cyrillic
		0,
	};

	//ImFont* name = io.Fonts->AddFontFromFileTTF("misc/fonts/Museo Sans Cyrl 700.ttf", 19.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//ImFont* icons = io.Fonts->AddFontFromMemoryTTF((void*)icon, sizeof(icon), 44, &font_config, ranges);
	//ImFont* weapon_icons = io.Fonts->AddFontFromFileTTF("misc/fonts/icomoon.ttf", 38.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	static bool tester = true;
	//if (GetKeyState(VK_HOME) & 1) {
	//	tester = !tester;
	//}

	static bool one = true;
	static bool two = false;
	static int sel1 = 0;
	static int sl = 0;
	auto s = ImVec2{}, p = ImVec2{}, gs = ImVec2{ 620, 460 };
	ImGui::SetNextWindowSize(ImVec2(gs));

	if (tester) {
		ImGui::GetIO().MouseDrawCursor = tester;
		ImGui::Begin("##GUI", NULL, ImGuiWindowFlags_::ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_::ImGuiWindowFlags_NoBackground);
		{
			{//draw
				s = ImVec2(ImGui::GetWindowSize().x - ImGui::GetStyle().WindowPadding.x * 2, ImGui::GetWindowSize().y - ImGui::GetStyle().WindowPadding.y * 2); p = ImVec2(ImGui::GetWindowPos().x + ImGui::GetStyle().WindowPadding.x, ImGui::GetWindowPos().y + ImGui::GetStyle().WindowPadding.y); auto draw = ImGui::GetWindowDrawList();
				draw->AddRectFilled(p, ImVec2(p.x + s.x, p.y + s.y), ImColor(33, 33, 33)); //tabs
				draw->AddRectFilled(ImVec2(p.x, p.y + 25), ImVec2(p.x + s.x, p.y + s.y - 25), ImColor(25, 25, 25));

				draw->AddLine(ImVec2(p.x, p.y + 25), ImVec2(p.x + s.x, p.y + 25), ImColor(89, 113, 162)); // tab seperator

				draw->AddLine(ImVec2(p.x, p.y + s.y - 25), ImVec2(p.x + s.x, p.y + s.y - 25), ImColor(89, 113, 162)); // bottom seperator
			}
			{//tabs
				ImGui::PushFont(font);
				ImGui::SetCursorPosX(20);
				ImGui::SetCursorPosY(10);
				ImGui::BeginGroup();

				if (ImGui::tab("Rage", tab == 1))tab = 1; ImGui::SameLine();
				if (ImGui::tab("Visuals", tab == 3))tab = 3; ImGui::SameLine();
				if (ImGui::tab("Misc", tab == 4))tab = 4; ImGui::SameLine();
				if (ImGui::tab("Config", tab == 6))tab = 6;
				ImGui::EndGroup();
				ImGui::PopFont();
			}
			{//content
				if (tab == 1)
				{
					ImGui::PushFont(font);
					{//left upper
						ImGui::SetCursorPosY(35);
						ImGui::BeginGroup();
						ImGui::SetCursorPosX(15);
						ImGui::MenuChild("Aimbot", ImVec2(300, 205), false);
						{
							ImGui::Checkbox("Master Switch", &SETTINGS::ragebot_configs.aimbot_enabled);
							ImGui::Checkbox("Ignore limbs when moving", &SETTINGS::ragebot_configs.aimbot_ignore_limbs_when_moving);
							ImGui::Checkbox("Auto Crouch", &SETTINGS::ragebot_configs.aimbot_autocrouch_enabled);
							ImGui::Checkbox("Autostop", &SETTINGS::ragebot_configs.aimbot_autostop_type);
							if (SETTINGS::ragebot_configs.aimbot_autostop_type)
							{
								ImGui::SliderInt("Damage to trigger##trigger damage", &SETTINGS::ragebot_configs.aimbot_autostop_damage_trigger, 0.f, 110.f);
							}
							//ImGui::Checkbox("Auto Crouch", &SETTINGS::ragebot_configs.aimbot_enabled);

						}
						ImGui::EndChild();
						ImGui::EndGroup();
					}
					{//left bottom
						ImGui::SetCursorPosY(240);
						ImGui::BeginGroup();
						ImGui::SetCursorPosX(15);
						ImGui::MenuChild("Other", ImVec2(300, 180), false);
						{

						}
						ImGui::EndChild();
						ImGui::EndGroup();
					}
					{//right
						ImGui::SetCursorPosY(35);
						ImGui::BeginGroup();
						ImGui::SetCursorPosX(320);
						ImGui::MenuChild("Settings", ImVec2(285, 385), false);
						{

						}
						ImGui::EndChild();
						ImGui::EndGroup();
						ImGui::PopFont();
					}
				}
			}
		}
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return pEndScene(pDevice); // call original endScene 
}


LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK EnumWindowsCallback(HWND handle, LPARAM lParam)
{
	DWORD wndProcId;
	GetWindowThreadProcessId(handle, &wndProcId);

	if (GetCurrentProcessId() != wndProcId)
		return TRUE; // skip to next window

	window = handle;
	return FALSE; // window found abort search
}

HWND GetProcessWindow()
{
	window = NULL;
	EnumWindows(EnumWindowsCallback, NULL);
	return window;
}

DWORD WINAPI MainThread(LPVOID lpReserved)
{
	bool attached = false;
	do
	{
		//if (kiero::init(kiero::RenderType::D3D9) == kiero::Status::Success)
		//{
			//kiero::bind(42, (void**)&oEndScene, hkEndScene);
			do
				window = GetProcessWindow();
			while (window == NULL);
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWL_WNDPROC, (LONG_PTR)WndProc);
			attached = true;
		//}
	} while (!attached);
	return TRUE;
}


void hookEndScene() {
	IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION); // create IDirect3D9 object
	if (!pD3D)
		return;

	D3DPRESENT_PARAMETERS d3dparams = { 0 };
	d3dparams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dparams.hDeviceWindow = GetForegroundWindow();
	d3dparams.Windowed = true;

	IDirect3DDevice9* pDevice = nullptr;

	HRESULT result = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, d3dparams.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dparams, &pDevice);
	if (FAILED(result) || !pDevice) {
		pD3D->Release();
		return;
	}
	//if device creation worked out -> lets get the virtual table:
	void** vTable = *reinterpret_cast<void***>(pDevice);

	//now detour:

	pEndScene = (endScene)DetourFunction((PBYTE)vTable[42], (PBYTE)hookedEndScene);

	pDevice->Release();
	pD3D->Release();
}

DWORD __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(DllHandle, 0);
	return 0;
}

DWORD WINAPI Menue(HINSTANCE hModule) {
	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout); //sets cout to be used with our newly created console

	hookEndScene();

	while (true) {
		Sleep(50);
		if (GetAsyncKeyState(VK_NUMPAD0)) {
			DetourRemove((PBYTE)pEndScene, (PBYTE)hookedEndScene); //unhook to avoid game crash
			break;
		}
	}
	std::cout << "ight imma head out" << std::endl;
	Sleep(1000);
	fclose(fp);
	FreeConsole();
	CreateThread(0, 0, EjectThread, 0, 0, 0);
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE Instance, DWORD Reason, LPVOID Reserved)
{
	switch (Reason)
	{
		case DLL_PROCESS_ATTACH:
		{
			CreateDirectoryA(enc_char("C:\\Bameware"), NULL);
			CreateDirectoryA(enc_char("C:\\Bameware\\Logs"), NULL);
			CreateDirectoryA(enc_char("C:\\Bameware\\Configs"), NULL);
			CreateDirectoryA(enc_char("C:\\Bameware\\Resources"), NULL);
			CreateDirectoryA(enc_char("C:\\Bameware\\Resources\\Fonts"), NULL);

			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Start, NULL, NULL, NULL);
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Menue, NULL, 0, NULL);
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, NULL, 0, NULL);
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			LOG("DETACHING");
#ifdef DEV_MODE
			{
				fclose(stdin);
				fclose(stdout);
				FreeConsole();
			}
#endif

			HOOKS::UnHook();

			break;
		}
	}

	return true;
}
