// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044AC10 rf_mission_countdown_hud_render
// UNREALRED VERIFIED [hud-late-pass] Formats global countdown time as %02d:%04.1f and renders it with hud.tbl countdown position/color and the rfpc-large.vf handle.
int rf_mission_countdown_hud_render()
{
  int v1; // [esp+8h] [ebp-2Ch]
  char Buffer[32]; // [esp+Ch] [ebp-28h] BYREF
  float v3; // [esp+30h] [ebp-4h]

  v1 = (int)rf_mission_countdown_remaining_seconds / 60;
  v3 = rf_mission_countdown_remaining_seconds - (double)v1 * 60.0;
  sprintf(Buffer, "%02d:%04.1f", v1, v3);
  rf_render_color_set_packed_rgba8(rf_hud_countdown_color);
  return rf_font_draw_text_screen(
           rf_hud_countdown_x,
           rf_hud_countdown_y,
           (unsigned __int8 *)Buffer,
           rf_hud_countdown_font,
           unk_182ABBC);
}

