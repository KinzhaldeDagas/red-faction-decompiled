// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044EFB0 rf_hud_ammo_noclip_render
// UNREALRED VERIFIED [hud-ammo-general] Renders the no-positive-clip ammo branch from the owning entity's reserve pool as one integer numeral.
// UNREALRED VERIFIED [hud-status-tint-general] No-positive-clip renderer. Its bar and red/green signal inherit the packed default HUD color; only the ammo icon resets the current color to white.
void __cdecl rf_hud_ammo_noclip_render(int a1, int a2)
{
  unsigned __int8 *v2; // eax
  unsigned __int8 *v3; // eax
  unsigned int v4; // [esp-8h] [ebp-4Ch]
  int v5; // [esp-8h] [ebp-4Ch]
  int v6; // [esp-4h] [ebp-48h]
  int v7; // [esp-4h] [ebp-48h]
  _DWORD *v8; // [esp+4h] [ebp-40h]
  _DWORD v9[2]; // [esp+14h] [ebp-30h] BYREF
  int v10; // [esp+1Ch] [ebp-28h]
  int viewport_width; // [esp+20h] [ebp-24h] BYREF
  int viewport_height; // [esp+24h] [ebp-20h] BYREF
  int v13; // [esp+28h] [ebp-1Ch]
  int v14; // [esp+2Ch] [ebp-18h]
  const char *v15[2]; // [esp+30h] [ebp-14h] BYREF
  int v16; // [esp+40h] [ebp-4h]

  v10 = *(_DWORD *)(a1 + 4 * dword_912024[340 * a2] + 684);
  v13 = rf_hud_ammo_icon_resolve(a2);
  rf_string_construct_empty(v15);
  v16 = 0;
  viewport_width = rf_renderer_get_viewport_width();
  viewport_height = rf_renderer_get_viewport_height();
  rf_render_color_set_packed_rgba8(rf_hud_color_default_rgba);
  rf_render_color_set_alpha8((int)((double)unk_6EE6C7 * flt_661888));
  rf_bitmap_draw_unscaled_clipped(dword_6618BC, unk_6EDF80, unk_6EDF84, unk_187CD38);
  if ( v10 <= 0 )
    rf_bitmap_draw_unscaled_clipped(dword_6618F0, unk_6EDF88, unk_6EDF8C, unk_187CD38);
  else
    rf_bitmap_draw_unscaled_clipped(dword_6618D4, unk_6EDF88, unk_6EDF8C, unk_187CD38);
  if ( v13 >= 0 )
  {
    rf_render_color_set_rgba8(255, 255, 255, (int)(flt_661888 * 255.0));
    rf_bitmap_draw_unscaled_clipped(v13, unk_6EDF90, unk_6EDF94, unk_187CD38);
  }
  rf_render_color_set_packed_rgba8((unsigned __int8 *)&rf_hud_color_mid_rgba);
  rf_render_color_set_alpha8((int)((double)unk_6EE6B7 * flt_661888));
  v8 = rf_string_format_int32_decimal(v9, v10);
  LOBYTE(v16) = 1;
  rf_string_assign_from_object(v15, (int)v8);
  LOBYTE(v16) = 0;
  rf_string_destroy_buffer(v9);
  v6 = dword_661690;
  v4 = rf_string_length_from_cstr(v15);
  v2 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v15);
  rf_font_measure_text_extent(&viewport_width, &viewport_height, v2, v4, v6);
  v14 = unk_6EDF98 + (unk_6EDFA0 - viewport_width) / 2;
  v7 = dword_182ABBC;
  v5 = dword_661690;
  v3 = (unsigned __int8 *)rf_string_object_c_str_or_empty(v15);
  rf_font_draw_text_screen(v14, unk_6EDF9C, v3, v5, v7);
  v16 = -1;
  rf_string_destroy_buffer(v15);
}

