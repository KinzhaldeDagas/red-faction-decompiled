// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00572AD0 rf_renderer_draw_circle_outline_clipped
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Recovered cdecl(centerX,centerY,radius,renderMode). Computes segment count=clamp(3*radius,5,128) using native signed 32-bit product, angular step6.283185482025146/count. Draws count-1 successive line segments at (centerX+radius*sin(angle),centerY+radius*cos(angle)), then explicitly closes last to angle0. Every segment uses clipped screen-line helper. Radius is not validated; zero degenerates all segments and negative radius mirrors the circle.
void __cdecl rf_renderer_draw_circle_outline_clipped(int center_x, int center_y, int radius, int render_mode)
{
  float v4; // [esp+14h] [ebp-88h]
  float v5; // [esp+18h] [ebp-84h]
  float v6; // [esp+1Ch] [ebp-80h]
  float v7; // [esp+20h] [ebp-7Ch]
  float v8; // [esp+44h] [ebp-58h]
  float v9; // [esp+48h] [ebp-54h]
  float v10; // [esp+4Ch] [ebp-50h]
  float v11; // [esp+50h] [ebp-4Ch]
  float v12; // [esp+5Ch] [ebp-40h]
  float v13; // [esp+68h] [ebp-34h]
  int v14; // [esp+7Ch] [ebp-20h] BYREF
  float v15; // [esp+80h] [ebp-1Ch]
  float v16; // [esp+84h] [ebp-18h]
  float v17; // [esp+88h] [ebp-14h]
  int i; // [esp+8Ch] [ebp-10h]
  float v19; // [esp+90h] [ebp-Ch]
  float v20; // [esp+94h] [ebp-8h]
  float v21; // [esp+98h] [ebp-4h]

  v21 = 0.0;
  v14 = 3 * radius;
  rf_integer_clamp_in_place(&v14, 5, 128);
  v16 = 6.283185482025146 / (double)v14;
  for ( i = 0; i < v14 - 1; ++i )
  {
    v15 = rf_sin_float(v21) * (double)radius;
    v17 = rf_cos_float(v21) * (double)radius;
    v13 = v21 + v16;
    v19 = rf_sin_float(v13) * (double)radius;
    v12 = v21 + v16;
    v20 = rf_cos_float(v12) * (double)radius;
    v11 = (double)center_y + v20;
    v10 = (double)center_x + v19;
    v9 = (double)center_y + v17;
    v8 = (double)center_x + v15;
    rf_renderer_draw_screen_line_clipped(v8, v9, v10, v11, render_mode);
    v21 = v21 + v16;
  }
  v15 = rf_sin_float(v21) * (double)radius;
  v17 = rf_cos_float(v21) * (double)radius;
  v19 = rf_sin_float(0.0) * (double)radius;
  v20 = rf_cos_float(0.0) * (double)radius;
  v7 = (double)center_y + v20;
  v6 = (double)center_x + v19;
  v5 = (double)center_y + v17;
  v4 = (double)center_x + v15;
  rf_renderer_draw_screen_line_clipped(v4, v5, v6, v7, render_mode);
}

