// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00573E80 rf_bitmap_mip_chain_pixel_count
// UNREALRED VERIFIED [bitmap-lifecycle-20261028]: Arguments width,height,mip count. Sums width*height for each requested level; after each level halves signed dimensions and clamps each to at least1. Returns signed integer sum, not byte count. Nonpositive mip count returns0. Initial width/height are not clamped before first product; no overflow or sensible mip count check.
int __cdecl rf_bitmap_mip_chain_pixel_count(int a1, int a2, int a3)
{
  int v4; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  v4 = 0;
  for ( i = 0; i < a3; ++i )
  {
    v4 += a2 * a1;
    a1 = rf_int_max(1, a1 / 2);
    a2 = rf_int_max(1, a2 / 2);
  }
  return v4;
}

