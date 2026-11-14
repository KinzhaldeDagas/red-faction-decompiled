// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00572750 rf_renderer_draw_screen_line_clipped
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Clips floating endpoints against inclusive relative X/Y clip bounds. Swaps endpoints to make y1<=y2, then branches by horizontal direction and intersects X boundaries before Y boundaries, rejecting disjoint segments. Backend102 receives clipped endpoints and caller render mode through screen-line backend. No line submitted on other backends. Intersection divides occur only inside corresponding crossing branches; no explicit NaN/finite input checks or integer rounding here.
void __cdecl rf_renderer_draw_screen_line_clipped(float a1, float a2, float a3, float a4, int a5)
{
  float v5; // [esp+18h] [ebp-24h]
  float v6; // [esp+1Ch] [ebp-20h]
  float v7; // [esp+20h] [ebp-1Ch]
  float v8; // [esp+20h] [ebp-1Ch]
  float v9; // [esp+20h] [ebp-1Ch]
  float v10; // [esp+20h] [ebp-1Ch]
  float v11; // [esp+20h] [ebp-1Ch]
  float v12; // [esp+20h] [ebp-1Ch]
  float v13; // [esp+20h] [ebp-1Ch]
  float v14; // [esp+20h] [ebp-1Ch]
  float v15; // [esp+24h] [ebp-18h]
  float v16; // [esp+2Ch] [ebp-10h]
  float v17; // [esp+30h] [ebp-Ch]
  float v18; // [esp+38h] [ebp-4h]

  v18 = (float)dword_187CCD4;
  v15 = (float)dword_187CCDC;
  v16 = (float)dword_187CCD8;
  v17 = (float)dword_187CCE0;
  if ( a4 < (double)a2 )
  {
    v6 = a2;
    a2 = a4;
    a4 = v6;
    v5 = a1;
    a1 = a3;
    a3 = v5;
  }
  if ( v15 <= (double)a4 && v17 >= (double)a2 )
  {
    if ( a3 <= (double)a1 )
    {
      if ( v18 > (double)a1 || v16 < (double)a3 )
        return;
      if ( v16 < (double)a1 )
      {
        v11 = (a4 - a2) * (a1 - v16) / (a1 - a3);
        a2 = a2 + v11;
        if ( v17 < (double)a2 )
          return;
        a1 = (float)dword_187CCD8;
      }
      if ( v18 > (double)a3 )
      {
        v12 = (a4 - a2) * (v18 - a3) / (a1 - a3);
        a4 = a4 - v12;
        if ( v15 > (double)a4 )
          return;
        a3 = (float)dword_187CCD4;
      }
      if ( v15 > (double)a2 )
      {
        v13 = (a1 - a3) * (v15 - a2) / (a4 - a2);
        a1 = a1 - v13;
        a2 = (float)dword_187CCDC;
      }
      if ( v17 < (double)a4 )
      {
        v14 = (a1 - a3) * (a4 - v17) / (a4 - a2);
        a3 = a3 + v14;
        a4 = (float)dword_187CCE0;
      }
    }
    else
    {
      if ( v18 > (double)a3 || v16 < (double)a1 )
        return;
      if ( v18 > (double)a1 )
      {
        v7 = (a4 - a2) * (v18 - a1) / (a3 - a1);
        a2 = a2 + v7;
        if ( v17 < (double)a2 )
          return;
        a1 = (float)dword_187CCD4;
      }
      if ( v16 < (double)a3 )
      {
        v8 = (a4 - a2) * (a3 - v16) / (a3 - a1);
        a4 = a4 - v8;
        if ( v15 > (double)a4 )
          return;
        a3 = (float)dword_187CCD8;
      }
      if ( v15 > (double)a2 )
      {
        v9 = (a3 - a1) * (v15 - a2) / (a4 - a2);
        a1 = a1 + v9;
        a2 = (float)dword_187CCDC;
      }
      if ( v17 < (double)a4 )
      {
        v10 = (a3 - a1) * (a4 - v17) / (a4 - a2);
        a3 = a3 - v10;
        a4 = (float)dword_187CCE0;
      }
    }
    if ( dword_187CC9C == 102 )
      rf_renderer_draw_screen_line_backend_102(a1, a2, a3, a4, a5);
  }
}

