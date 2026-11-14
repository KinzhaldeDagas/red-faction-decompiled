// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005721E0 rf_bitmap_draw_unscaled_clipped
// UNREALRED VERIFIED [hud-viewport-20261027] Bitmap dimensions from 0x576450 define destination extent x+width-1 / y+height-1. Integer clip rectangle trims destination and matching source offsets. The 0x5D2F10 submission receives equal source/destination visible widths/heights: native status art remains 1:1 pixels, not stretched independently by viewport axes.
void __cdecl rf_bitmap_draw_unscaled_clipped(unsigned int a1, int a2, int a3, int a4)
{
  int v4; // [esp+4h] [ebp-20h]
  int v5; // [esp+8h] [ebp-1Ch]
  int v6; // [esp+Ch] [ebp-18h]
  int v7; // [esp+10h] [ebp-14h]
  int v8; // [esp+14h] [ebp-10h] BYREF
  int v9; // [esp+18h] [ebp-Ch]
  int v10; // [esp+1Ch] [ebp-8h] BYREF
  int v11; // [esp+20h] [ebp-4h]

  rf_bitmap_get_resolved_dimensions(a1, &v10, &v8);
  if ( v10 )
  {
    v4 = a2;
    v9 = a2 + v10 - 1;
    v5 = a3;
    v6 = a3 + v8 - 1;
    v7 = 0;
    v11 = 0;
    if ( a2 <= dword_187CCD8 && v9 >= dword_187CCD4 && a3 <= dword_187CCE0 && v6 >= dword_187CCDC )
    {
      if ( a2 < dword_187CCD4 )
      {
        v7 = dword_187CCD4 - a2;
        v4 = dword_187CCD4;
      }
      if ( a3 < dword_187CCDC )
      {
        v11 = dword_187CCDC - a3;
        v5 = dword_187CCDC;
      }
      if ( v9 > dword_187CCD8 )
        v9 = dword_187CCD8;
      if ( v6 > dword_187CCE0 )
        v6 = dword_187CCE0;
      if ( v7 >= 0 && v11 >= 0 && v7 < v10 && v11 < v8 && dword_187CC9C == 102 )
        rf_renderer_blit_bitmap_subrectangle_backend_102(
          a1,
          v4,
          v5,
          v9 - v4 + 1,
          v6 - v5 + 1,
          v7,
          v11,
          v9 - v4 + 1,
          v6 - v5 + 1,
          0,
          0,
          a4);
    }
  }
}

