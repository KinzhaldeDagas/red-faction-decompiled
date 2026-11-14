// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00572FC0 rf_renderer_draw_rectangle_outline_clipped
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Computes signed-size inclusive endpoints (positive extent -1, nonpositive +1), normalizes/clips them to current relative bounds, and calls line helper four times with global render mode187CC5C. VERIFIED original behavior: draws top left-to-right, right top-to-bottom, bottom right-to-left, then TOP right-to-left again. The left edge is omitted. No corrective patch applied.
void __cdecl rf_renderer_draw_rectangle_outline_clipped(int a1, int a2, int a3, int a4)
{
  double v4; // st7
  double v5; // st7
  float v6; // [esp+14h] [ebp-18h]
  float v7; // [esp+18h] [ebp-14h]
  float v8; // [esp+1Ch] [ebp-10h]
  float v9; // [esp+20h] [ebp-Ch]
  float v10; // [esp+24h] [ebp-8h]
  float v11; // [esp+28h] [ebp-4h]

  v8 = (float)a1;
  v9 = (float)a2;
  if ( a3 <= 0 )
    v4 = (double)a1 + (double)a3 + 1.0;
  else
    v4 = (double)a1 + (double)a3 - 1.0;
  v10 = v4;
  if ( a4 <= 0 )
    v5 = (double)a2 + (double)a4 + 1.0;
  else
    v5 = (double)a2 + (double)a4 - 1.0;
  v11 = v5;
  if ( v8 > (double)v10 )
  {
    v7 = (float)a1;
    v8 = v10;
    v10 = v7;
  }
  if ( v9 > (double)v11 )
  {
    v6 = (float)a2;
    v9 = v5;
    v11 = v6;
  }
  if ( v8 <= (double)dword_187CCD8
    && v10 >= (double)dword_187CCD4
    && v9 <= (double)dword_187CCE0
    && v11 >= (double)dword_187CCDC )
  {
    if ( v8 < (double)dword_187CCD4 )
      v8 = (float)dword_187CCD4;
    if ( v9 < (double)dword_187CCDC )
      v9 = (float)dword_187CCDC;
    if ( v10 > (double)dword_187CCD8 )
      v10 = (float)dword_187CCD8;
    if ( v11 > (double)dword_187CCE0 )
      v11 = (float)dword_187CCE0;
    rf_renderer_draw_screen_line_clipped(v8, v9, v10, v9, dword_187CC5C);
    rf_renderer_draw_screen_line_clipped(v10, v9, v10, v11, dword_187CC5C);
    rf_renderer_draw_screen_line_clipped(v10, v11, v8, v11, dword_187CC5C);
    rf_renderer_draw_screen_line_clipped(v10, v9, v8, v9, dword_187CC5C);
  }
}

