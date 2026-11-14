// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E1B00 rf_player_viewport_mode_set
// UNREALRED VERIFIED [weapon-holding-variants] Builds the viewport rectangle and base FOV for modes 0..7, then persists the selected mode at Player+0xDC. Modes 2 and 3 are the top and bottom two-player split-screen views.
int __cdecl rf_player_viewport_mode_set(int a1, int a2)
{
  int result; // eax
  int physical_screen_width; // eax
  int v4; // esi
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // [esp-Ch] [ebp-18h]
  int v13; // [esp-8h] [ebp-14h]
  int v14; // [esp-8h] [ebp-14h]
  int v15; // [esp-8h] [ebp-14h]
  int v16; // [esp-8h] [ebp-14h]
  int v17; // [esp-8h] [ebp-14h]
  int physical_screen_height; // [esp-4h] [ebp-10h]
  int v19; // [esp-4h] [ebp-10h]
  int v20; // [esp-4h] [ebp-10h]
  int v21; // [esp-4h] [ebp-10h]
  int v22; // [esp-4h] [ebp-10h]
  int v23; // [esp-4h] [ebp-10h]
  int v24; // [esp-4h] [ebp-10h]
  int v25; // [esp-4h] [ebp-10h]

  result = a2;
  switch ( a2 )
  {
    case 0:
      physical_screen_height = rf_renderer_get_physical_screen_height();
      physical_screen_width = rf_renderer_get_physical_screen_width();
      result = rf_player_set_four_dword_payload200_and_float216(
                 a1,
                 0,
                 0,
                 physical_screen_width,
                 physical_screen_height,
                 90.0);
      break;
    case 1:
      v4 = rf_renderer_get_physical_screen_height();
      v19 = v4 - 2 * (rf_renderer_get_physical_screen_height() / 8);
      v13 = rf_renderer_get_physical_screen_width();
      v5 = rf_renderer_get_physical_screen_height();
      result = rf_player_set_four_dword_payload200_and_float216(a1, 0, v5 / 8, v13, v19, 115.0);
      break;
    case 2:
      v20 = rf_renderer_get_physical_screen_height() / 2;
      v6 = rf_renderer_get_physical_screen_width();
      result = rf_player_set_four_dword_payload200_and_float216(a1, 0, 0, v6, v20, 90.0);
      break;
    case 3:
      v21 = rf_renderer_get_physical_screen_height() / 2;
      v14 = rf_renderer_get_physical_screen_width();
      v7 = rf_renderer_get_physical_screen_height();
      result = rf_player_set_four_dword_payload200_and_float216(a1, 0, v7 / 2, v14, v21, 90.0);
      break;
    case 4:
      v22 = rf_renderer_get_physical_screen_height() / 2;
      v8 = rf_renderer_get_physical_screen_width();
      result = rf_player_set_four_dword_payload200_and_float216(a1, 0, 0, v8 / 2, v22, 90.0);
      break;
    case 5:
      v23 = rf_renderer_get_physical_screen_height() / 2;
      v15 = rf_renderer_get_physical_screen_width() / 2;
      v9 = rf_renderer_get_physical_screen_width();
      result = rf_player_set_four_dword_payload200_and_float216(a1, v9 / 2, 0, v15, v23, 90.0);
      break;
    case 6:
      v24 = rf_renderer_get_physical_screen_height() / 2;
      v16 = rf_renderer_get_physical_screen_width() / 2;
      v10 = rf_renderer_get_physical_screen_height();
      result = rf_player_set_four_dword_payload200_and_float216(a1, 0, v10 / 2, v16, v24, 90.0);
      break;
    case 7:
      v25 = rf_renderer_get_physical_screen_height() / 2;
      v17 = rf_renderer_get_physical_screen_width() / 2;
      v12 = rf_renderer_get_physical_screen_height() / 2;
      v11 = rf_renderer_get_physical_screen_width();
      result = rf_player_set_four_dword_payload200_and_float216(a1, v11 / 2, v12, v17, v25, 90.0);
      break;
    default:
      break;
  }
  *(_DWORD *)(a1 + 220) = a2;
  return result;
}

