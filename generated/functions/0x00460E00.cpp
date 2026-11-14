// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00460E00 rf_multiplayer_profile_draw_panel_and_portrait
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Cdecl logical panelX,store parentX6F4AE8 FIRST. Set RGBA(0,0,0,128),fill scaled rectangle((parentX+105),(parentY+10),parentWidth,(parentHeight-20)),all
// truncTowardZero,draw parent46FD70. Unguarded bitmapCache6F4A58[selectedIndex6F4AD8] ->resolved dimensions. Compute scaled portrait control absoluteXY and size273x239;set
// whiteRGBA,blit WHOLE source bitmap(0,0,sourceWidth,sourceHeight) into scaled destination with zero extra flags and backend187CD34. No index/bitmap/dimension check. Then draw
// EVERY6F4FC0 control via vtable0/ECXthis with NO stack args;decompiler's seven-arg presentation false. Query raw profile-inputAL460530;zero clears editLatch6F4AD5,nonzero preserves.
// No name commit,animation integration or prior-color restore.
unsigned __int8 __cdecl rf_multiplayer_profile_draw_panel_and_portrait(int a1)
{
  _DWORD *v1; // eax
  unsigned __int8 result; // al
  int v3; // [esp+4h] [ebp-30h]
  int v4; // [esp+8h] [ebp-2Ch]
  int v5; // [esp+Ch] [ebp-28h]
  int v6; // [esp+10h] [ebp-24h]
  int v7; // [esp+14h] [ebp-20h]
  int i; // [esp+18h] [ebp-1Ch]
  int v9; // [esp+1Ch] [ebp-18h] BYREF
  int v10; // [esp+20h] [ebp-14h]
  int v11; // [esp+24h] [ebp-10h]
  int v12; // [esp+28h] [ebp-Ch] BYREF
  int v13; // [esp+2Ch] [ebp-8h]
  int v14; // [esp+30h] [ebp-4h]

  unk_6F4AE8 = a1;
  rf_render_color_set_rgba8(0, 0, 0, 128);
  v7 = unk_6F4AE8 + 105;
  v10 = (int)((double)(unk_6F4AE8 + 105) * rf_ui_scale_x);
  v6 = unk_6F4AEC + 10;
  v11 = (int)((double)(unk_6F4AEC + 10) * rf_ui_scale_y);
  v14 = (int)((double)unk_6F4AF0 * rf_ui_scale_x);
  v5 = unk_6F4AF4 - 20;
  v13 = (int)((double)(unk_6F4AF4 - 20) * rf_ui_scale_y);
  rf_renderer_fill_rectangle_clipped(v10, v11, v14, v13, dword_182ABB8);
  rf_ui_panel_render_bitmap(dword_6F4ADC);
  rf_bitmap_get_resolved_dimensions(unk_6F4A58[dword_6F4AD8], &v9, &v12);
  v4 = rf_ui_control_absolute_x(&dword_6F4F94);
  v10 = (int)((double)v4 * rf_ui_scale_x);
  v3 = rf_ui_control_absolute_y(&dword_6F4F94);
  v11 = (int)((double)v3 * rf_ui_scale_y);
  v14 = (int)((double)unk_6F4FA8 * rf_ui_scale_x);
  v13 = (int)((double)unk_6F4FAC * rf_ui_scale_y);
  rf_render_color_set_rgba8(255, 255, 255, 255);
  rf_bitmap_blit_subrectangle_backend_dispatch(
    unk_6F4A58[dword_6F4AD8],
    v10,
    v11,
    v14,
    v13,
    0,
    0,
    v9,
    v12,
    0,
    0,
    unk_187CD34);
  for ( i = 0; i < rf_receiver_get_first_dword(dword_6F4FC0); ++i )
  {
    v1 = (_DWORD *)rf_inline_dword_array4_element_address_unchecked(dword_6F4FC0, i);
    (**(void (__thiscall ***)(_DWORD, _DWORD, int, int, int, int, int))*v1)(*v1, *v1, v3, v4, v5, v6, v7);
  }
  result = rf_multiplayer_profile_input_byte_get();
  if ( !result )
    unk_6F4AD5 = 0;
  return result;
}

