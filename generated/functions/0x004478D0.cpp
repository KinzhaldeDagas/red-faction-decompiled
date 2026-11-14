// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004478D0 rf_ui_draw_mouse_cursor
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, panel-stack transition and modal-frame flow, sound tables, message/binding expansion and native partial-state
// ownership and native signed/x87/stack/callback ABI): No arguments. On BYTE6EDD41==0 loads cursor.tga(-1,1), stores returned bitmap handle661674, and sets6EDD41=1 even on failure,
// so this body will not retry while that flag remains nonzero. Reads absolute mouse X/Y into local signed ints and cumulative wheel/Z into global193A03C; ignores reader status, which
// on disabled input supplies zeroes. Converts X/Y to FLOAT32 using FILD/FSTP. Sets renderer color white(255,255,255,255). Signed handle>0 draws unscaled clipped bitmap at original
// integer X/Y using LIVE187CD38. Otherwise sets color(96,160,0,255) and draws four clipped screen lines with separately FLOAT32-rounded coordinates: (x-1,y-1)-(x+1,y-1),
// (x-1,y+1)-(x+1,y+1), (x-4,y)-(x+4,y), and (x,y-4)-(x,y+4), sampling LIVE187CC5C before each line. Original PE doubles are1 and4; no coordinate clamp or x87 conditional comparison.
// Finally always sets white again and forwards that color-setter AL; it does not restore incoming color.
char rf_ui_draw_mouse_cursor()
{
  float v1; // [esp+14h] [ebp-40h]
  float v2; // [esp+18h] [ebp-3Ch]
  float v3; // [esp+1Ch] [ebp-38h]
  float v4; // [esp+20h] [ebp-34h]
  float v5; // [esp+24h] [ebp-30h]
  float v6; // [esp+2Ch] [ebp-28h]
  float v7; // [esp+30h] [ebp-24h]
  float v8; // [esp+34h] [ebp-20h]
  float v9; // [esp+3Ch] [ebp-18h]
  float v10; // [esp+40h] [ebp-14h]
  int v11; // [esp+44h] [ebp-10h] BYREF
  int v12; // [esp+48h] [ebp-Ch] BYREF
  float v13; // [esp+4Ch] [ebp-8h]
  float v14; // [esp+50h] [ebp-4h]

  if ( !unk_6EDD41 )
  {
    dword_661674 = rf_bitmap_load_with_optional_mipmap_generation("cursor.tga", (void *)0xFFFFFFFF, 1);
    unk_6EDD41 = 1;
  }
  rf_mouse_get_absolute_state(&v11, &v12, &unk_193A03C);
  v13 = (float)v11;
  v14 = (float)v12;
  rf_render_color_set_rgba8(255, 255, 255, 255);
  if ( dword_661674 <= 0 )
  {
    rf_render_color_set_rgba8(96, 160, 0, 255);
    v10 = v14 - 1.0;
    v9 = v13 + 1.0;
    v8 = v13 - 1.0;
    rf_renderer_draw_screen_line_clipped(v8, v10, v9, v10, dword_187CC5C);
    v7 = v14 + 1.0;
    v6 = v13 + 1.0;
    v5 = v13 - 1.0;
    rf_renderer_draw_screen_line_clipped(v5, v7, v6, v7, dword_187CC5C);
    v4 = v13 + 4.0;
    v3 = v13 - 4.0;
    rf_renderer_draw_screen_line_clipped(v3, v14, v4, v14, dword_187CC5C);
    v2 = v14 + 4.0;
    v1 = v14 - 4.0;
    rf_renderer_draw_screen_line_clipped(v13, v1, v13, v2, dword_187CC5C);
  }
  else
  {
    rf_bitmap_draw_unscaled_clipped(dword_661674, v11, v12, unk_187CD38);
  }
  return rf_render_color_set_rgba8(255, 255, 255, 255);
}

