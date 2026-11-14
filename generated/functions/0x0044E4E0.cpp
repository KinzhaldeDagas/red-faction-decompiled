// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044E4E0 rf_hud_ammo_clip_render
// UNREALRED VERIFIED [hud-status-font-20261027] Ordinary clip loaded/reserve numerals use BIG font handle 0x661690 for both measurement and drawing. Special-power 0x44E970 and no-clip 0x44EFB0 also consume that big handle. This differs deliberately from health/suit smallfont 0x661694; retain the distinction when scaling all glyphs uniformly.
int __cdecl rf_hud_ammo_clip_render(int a1, int a2, int a3, char a4)
{
  int v5; // [esp+38h] [ebp-11Ch]
  int viewport_width; // [esp+3Ch] [ebp-118h] BYREF
  int viewport_height; // [esp+40h] [ebp-114h] BYREF
  char Buffer; // [esp+44h] [ebp-110h] BYREF
  _BYTE v9[259]; // [esp+45h] [ebp-10Fh] BYREF
  int v10; // [esp+14Ch] [ebp-8h]
  int v11; // [esp+150h] [ebp-4h]

  v5 = *(_DWORD *)(a1 + 4 * dword_912024[340 * a2] + 684);
  v10 = rf_hud_ammo_icon_resolve(a2);
  viewport_width = rf_renderer_get_viewport_width();
  viewport_height = rf_renderer_get_viewport_height();
  rf_render_color_set_rgba8(255, 255, 255, 120);
  if ( a4 )
    rf_render_color_set_alpha8((int)(((double)unk_6EE6C7 * 0.300000011920929 + 0.5) * flt_661888));
  else
    rf_render_color_set_alpha8((int)((double)unk_6EE6C7 * flt_661888));
  rf_bitmap_draw_unscaled_clipped(dword_661890, unk_6EDF40, a3 + unk_6EDF44, unk_187CD38);
  if ( *(int *)(a1 + 4 * a2 + 812) <= 0 )
    rf_bitmap_draw_unscaled_clipped(dword_6618F0, unk_6EDF48, a3 + unk_6EDF4C, unk_187CD38);
  else
    rf_bitmap_draw_unscaled_clipped(dword_6618D4, unk_6EDF48, a3 + unk_6EDF4C, unk_187CD38);
  if ( v10 >= 0 )
  {
    rf_render_color_set_rgba8(255, 255, 255, (int)(flt_661888 * 255.0));
    rf_bitmap_draw_unscaled_clipped(v10, unk_6EDF50, a3 + unk_6EDF54, unk_187CD38);
  }
  rf_render_color_set_packed_rgba8((unsigned __int8 *)&rf_hud_color_full_rgba);
  if ( a4 )
    rf_render_color_set_alpha8((int)(((double)unk_6EE6C3 * 0.300000011920929 + 0.5) * flt_661888));
  else
    rf_render_color_set_alpha8((int)((double)unk_6EE6C3 * flt_661888));
  sprintf(&Buffer, "%d", *(_DWORD *)(a1 + 4 * a2 + 812));
  rf_font_measure_text_extent(
    &viewport_width,
    &viewport_height,
    (unsigned __int8 *)&Buffer,
    &v9[strlen(&Buffer)] - v9,
    dword_661690);
  v11 = unk_6EDF58 + (unk_6EDF60 - viewport_width) / 2;
  rf_font_draw_text_screen(v11, a3 + unk_6EDF5C, (unsigned __int8 *)&Buffer, dword_661690, dword_182ABBC);
  rf_render_color_set_packed_rgba8((unsigned __int8 *)&rf_hud_color_mid_rgba);
  if ( a4 )
    rf_render_color_set_alpha8((int)(((double)unk_6EE6B7 * 0.300000011920929 + 0.5) * flt_661888));
  else
    rf_render_color_set_alpha8((int)((double)unk_6EE6B7 * flt_661888));
  sprintf(&Buffer, "%d", v5);
  rf_font_measure_text_extent(
    &viewport_width,
    &viewport_height,
    (unsigned __int8 *)&Buffer,
    &v9[strlen(&Buffer)] - v9,
    dword_661690);
  v11 = unk_6EDF68 + (unk_6EDF70 - viewport_width) / 2;
  return rf_font_draw_text_screen(v11, a3 + unk_6EDF6C, (unsigned __int8 *)&Buffer, dword_661690, dword_182ABBC);
}

