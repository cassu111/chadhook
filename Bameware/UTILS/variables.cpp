#include "../includes.h"

#include "interfaces.h"

#include "../SDK/ISurface.h"
#include "render.h"
#include "../SDK/IEngine.h"

#include "../SDK/ConVar.h"


namespace GLOBAL
{
	HWND csgo_hwnd = FindWindow(0, "Counter-Strike: Global Offensive");

	bool should_send_packet;
	bool disable_fake_lag;
	bool is_fakewalking;
	bool should_choke_packets;
	bool is_freestanding;
	bool is_edging;
	bool can_shoot_someone;
	bool is_jumping;
	bool do_max_fake_lag;
	bool pressing_move;

	int choke_amount;
	float cheat_start_time;
	float lerp;

	float testing_float_1;
	float testing_float_2;
	bool testing_bool_1;
	bool testing_bool_2;

	void* last_cmd;

	Vector real_angles;
	Vector fake_angles;

	Vector strafe_angles;

	CColor synced_rainbow_color;
}

namespace FONTS
{
	unsigned int menu_tab_font;
	unsigned int menu_checkbox_font;
	unsigned int menu_slider_font;
	unsigned int menu_slider_value_font;
	unsigned int menu_groupbox_font;
	unsigned int menu_combobox_name_font;
	unsigned int menu_combobox_value_font;
	unsigned int menu_window_font;
	unsigned int menu_separator_font;
	unsigned int menu_window_blurr_font;
	unsigned int menu_keybind_value_font;
	unsigned int menu_keybind_name_font;
	unsigned int menu_text_input_name_font;
	unsigned int menu_text_input_value_font;
	unsigned int menu_button_font;
	unsigned int menu_colorpicker_font;
	unsigned int menu_tool_tip_font;

	unsigned int visuals_esp_font;
	unsigned int visuals_esp_font_small;
	unsigned int lby_indicator_font;
	unsigned int radio_indicator_font;
	unsigned int in_game_logging_font;
	unsigned int weapon_icon_font;
	unsigned int welcome_font;

	bool ShouldReloadFonts()
	{
		static int old_width, old_height;
		int width, height;
		INTERFACES::Engine->GetScreenSize(width, height);

		if (width != old_width || height != old_height)
		{
			old_width = width;
			old_height = height;
			return true;
		}
		return false;
	}

	void InitFonts()
	{
		static bool is_init = false;
		if (!is_init)
		{
			is_init = true;
			URLDownloadToFile(NULL, enc_char("https://drive.google.com/uc?authuser=0&id=1EQsMGkLKnXO0mcy_KIzpB6xntwDn7KiF&export=download"), enc_char("C:\\Bameware\\Resources\\Fonts\\againts.ttf"), NULL, NULL);
			AddFontResource(enc_char("C:\\Bameware\\Resources\\Fonts\\againts.ttf"));

			URLDownloadToFile(NULL, enc_char("https://drive.google.com/u/0/uc?id=1YKqts9yFiAe0VHURDU6KhnfA9wmTGvaK&export=download"), enc_char("C:\\Bameware\\Resources\\Fonts\\astriumwep.ttf"), NULL, NULL); //Weapon esp font
			AddFontResource(enc_char("C:\\Bameware\\Resources\\Fonts\\astriumwep.ttf"));
		}

		menu_tab_font = RENDER::CreateF("Verdana", 16, 650, 0, 0, SDK::FONTFLAG_DROPSHADOW);
		menu_checkbox_font = RENDER::CreateF("Verdana", 18, 650, 0, 0, NULL);
		menu_slider_font = RENDER::CreateF("Verdana", 18, 650, 0, 0, NULL);
		menu_slider_value_font = RENDER::CreateF("Verdana", 16, 650, 0, 0, NULL);
		menu_groupbox_font = RENDER::CreateF("Verdana", 18, 650, 0, 0, NULL);
		menu_combobox_name_font = RENDER::CreateF("Verdana", 18, 650, 0, 0, NULL);
		menu_combobox_value_font = RENDER::CreateF("Verdana", 16, 650, 0, 0, NULL);
		menu_separator_font = RENDER::CreateF("Verdana", 18, 650, 0, 0, NULL);
		menu_keybind_value_font = RENDER::CreateF("Verdana", 16, 650, 0, 0, NULL);
		menu_keybind_name_font = RENDER::CreateF("Verdana", 18, 650, 0, 0, NULL);
		menu_text_input_name_font = RENDER::CreateF("Verdana", 18, 650, 0, 0, NULL);
		menu_text_input_value_font = RENDER::CreateF("Verdana", 16, 650, 0, 0, NULL);
		menu_button_font = RENDER::CreateF("Verdana", 18, 650, 0, 0, NULL);
		menu_window_blurr_font = RENDER::CreateF("Verdana", 32, 650, 10, 0, NULL);
		menu_window_font = RENDER::CreateF("Verdana", 32, 650, 0, 10, NULL);
		menu_colorpicker_font = RENDER::CreateF("Verdana", 18, 650, 0, 0, NULL);
		menu_tool_tip_font = RENDER::CreateF("Verdana", 18, 650, 0, 0, NULL);

		visuals_esp_font = RENDER::CreateF("Verdana", 12, FW_MEDIUM, 0, 0, SDK::FONTFLAG_DROPSHADOW); // Tahoma //Verdana, 11, 500, outline
		visuals_esp_font_small = RENDER::CreateF("Verdana", 8, FW_NORMAL, 0, 0, SDK::FONTFLAG_OUTLINE);
		lby_indicator_font = RENDER::CreateF("Verdana", 28, 650, 0, 0, SDK::FONTFLAG_DROPSHADOW | SDK::FONTFLAG_ANTIALIAS);
		radio_indicator_font = RENDER::CreateF("Verdana", 12, 800, 0, 0, SDK::FONTFLAG_DROPSHADOW);
		in_game_logging_font = RENDER::CreateF("Verdana", 16, 800, 0, 0, SDK::FONTFLAG_DROPSHADOW);
		weapon_icon_font = RENDER::CreateF("Counter-Strike", 22, 450, 0, 0, SDK::FONTFLAG_ANTIALIAS);

		welcome_font = RENDER::CreateF("Againts", 100, 650, 0, 0, SDK::FONTFLAG_ANTIALIAS);
	}
}
