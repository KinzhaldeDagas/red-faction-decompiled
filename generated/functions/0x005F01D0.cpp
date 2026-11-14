// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F01D0 rf_ui_button_draw_direction_triangle
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Draws filled directional arrow as integer-stepped line segments in current color. Inner offsets ox=(w-4)/4+2,oy=(h-4)/4+2;inner extents W=w-2*ox-1,H=h-2*oy-1 at absolute position+offsets. Flags628:0x40/0x80 vertical triangle,0x40 points upward;else horizontal,0x100 points left,otherwise right. Bit0x40 takes priority over0x80;horizontal0x100 over0x200. Width/height divisors W/H have no zero guard for small gadget dimensions;negative extents can skip loops. Does not select render color or draw text.
void __thiscall rf_ui_button_draw_direction_triangle(_DWORD *this)
{
  float v1; // [esp+0h] [ebp-7Ch]
  float v2; // [esp+0h] [ebp-7Ch]
  float v3; // [esp+4h] [ebp-78h]
  float v4; // [esp+4h] [ebp-78h]
  float v5; // [esp+8h] [ebp-74h]
  float v6; // [esp+8h] [ebp-74h]
  float v7; // [esp+Ch] [ebp-70h]
  float v8; // [esp+Ch] [ebp-70h]
  int v10; // [esp+50h] [ebp-2Ch]
  int v11; // [esp+50h] [ebp-2Ch]
  bool v12; // [esp+57h] [ebp-25h]
  bool v13; // [esp+5Eh] [ebp-1Eh]
  int i; // [esp+60h] [ebp-1Ch]
  int j; // [esp+60h] [ebp-1Ch]
  int v16; // [esp+64h] [ebp-18h]
  int v17; // [esp+68h] [ebp-14h]
  int v18; // [esp+6Ch] [ebp-10h]
  int v19; // [esp+70h] [ebp-Ch]
  int v20; // [esp+74h] [ebp-8h]
  int v21; // [esp+74h] [ebp-8h]
  int v22; // [esp+78h] [ebp-4h]
  int v23; // [esp+78h] [ebp-4h]

  v22 = *(this + 5);
  v20 = *(this + 6);
  v19 = (v22 - 4) / 4 + 2;
  v16 = (v20 - 4) / 4 + 2;
  v17 = v19 + rf_ui_gadget_absolute_x(this, 0);
  v18 = v16 + rf_ui_gadget_absolute_y(this, 0);
  v23 = v22 - 2 * v19 - 1;
  v21 = v20 - 2 * v16 - 1;
  v13 = (*(this + 157) & 0x40) != 0;
  v12 = (*(this + 157) & 0x100) != 0;
  if ( (*(this + 157) & 0x40) != 0 || (*(this + 157) & 0x80) != 0 )
  {
    for ( i = 0; i <= v23; ++i )
    {
      v10 = 2 * v21 * i / v23;
      if ( 2 * v21 * (v23 - i) / v23 < v10 )
        v10 = 2 * v21 * (v23 - i) / v23;
      if ( v13 )
      {
        v7 = (float)(v21 + v18);
        v5 = (float)(i + v17);
        v3 = (float)(v21 + v18 - v10);
      }
      else
      {
        v7 = (float)(v10 + v18);
        v5 = (float)(i + v17);
        v3 = (float)v18;
      }
      v1 = (float)(i + v17);
      rf_renderer_draw_screen_line_clipped(v1, v3, v5, v7, dword_187CC5C);
    }
  }
  else
  {
    for ( j = 0; j <= v21; ++j )
    {
      v11 = 2 * v23 * j / v21;
      if ( 2 * v23 * (v21 - j) / v21 < v11 )
        v11 = 2 * v23 * (v21 - j) / v21;
      v8 = (float)(j + v18);
      if ( v12 )
      {
        v6 = (float)(v23 + v17);
        v4 = v8;
        v2 = (float)(v23 + v17 - v11);
      }
      else
      {
        v6 = (float)(v11 + v17);
        v4 = v8;
        v2 = (float)v17;
      }
      rf_renderer_draw_screen_line_clipped(v2, v4, v6, v8, dword_187CC5C);
    }
  }
}

