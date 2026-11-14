// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571F80 rf_bitmap_blit_unscaled_subrectangle_clipped
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Eight args: bitmap, destination x/y/width/height, source x/y, render mode. Gets bitmap dimensions, rejects disjoint destination against inclusive relative clip bounds, trims left/top while advancing source coordinates, trims right/bottom, then adjusts negative source origins and retries clipping. Limits extent to remaining bitmap source dimensions and rejects widths/heights<1. For backend102 forwards source/destination sizes equally, no flips, to backend blitter. Does not scale, add viewport origin here, allocate or write CPU pixels.
void __cdecl rf_bitmap_blit_unscaled_subrectangle_clipped(
        unsigned int a1,
        int a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8)
{
  int v8; // [esp+4h] [ebp-1Ch]
  int v9; // [esp+8h] [ebp-18h] BYREF
  int v10; // [esp+Ch] [ebp-14h]
  int v11; // [esp+10h] [ebp-10h]
  int v12; // [esp+14h] [ebp-Ch]
  int v13; // [esp+18h] [ebp-8h] BYREF
  int v14; // [esp+1Ch] [ebp-4h]
  int v15; // [esp+34h] [ebp+14h]
  int v16; // [esp+38h] [ebp+18h]

  v8 = a2;
  v14 = a2 + a4 - 1;
  v11 = a3;
  v12 = a3 + a5 - 1;
  rf_bitmap_get_resolved_dimensions(a1, &v9, &v13);
  while ( 1 )
  {
    v10 = 0;
    if ( v8 > dword_187CCD8 || v14 < dword_187CCD4 || v11 > dword_187CCE0 || v12 < dword_187CCDC )
      break;
    if ( v8 < dword_187CCD4 )
    {
      a6 += dword_187CCD4 - v8;
      v8 = dword_187CCD4;
    }
    if ( v11 < dword_187CCDC )
    {
      a7 += dword_187CCDC - v11;
      v11 = dword_187CCDC;
    }
    if ( v14 > dword_187CCD8 )
      v14 = dword_187CCD8;
    if ( v12 > dword_187CCE0 )
      v12 = dword_187CCE0;
    if ( a6 < 0 )
    {
      v8 -= a6;
      a6 = 0;
      v10 = 1;
    }
    if ( a7 < 0 )
    {
      v11 -= a7;
      a7 = 0;
      v10 = 1;
    }
    v15 = v14 - v8 + 1;
    v16 = v12 - v11 + 1;
    if ( v15 + a6 > v9 )
    {
      v15 = v9 - a6;
      v14 = v8 + v9 - a6 - 1;
    }
    if ( v16 + a7 > v13 )
    {
      v16 = v13 - a7;
      v12 = v11 + v13 - a7 - 1;
    }
    if ( v15 < 1 || v16 < 1 )
      break;
    if ( !v10 )
    {
      if ( dword_187CC9C == 102 )
        rf_renderer_blit_bitmap_subrectangle_backend_102(
          a1,
          v8,
          v11,
          v14 - v8 + 1,
          v12 - v11 + 1,
          a6,
          a7,
          v14 - v8 + 1,
          v12 - v11 + 1,
          0,
          0,
          a8);
      return;
    }
  }
}

