// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DF900 rf_renderer_cache_indexed_triangle_normal
// UNREALRED VERIFIED [renderer-helpers-20261028]: If recordDWORD+124 bit1 clear,loads THREE vertex indices from record+20/+24/+28,addresses12-byte positions in caller vertex array,and calls0x559A30(outputrecord+96,p0,p1,p2). Normalizes result with rf_vector_normalize_reciprocal_sqrt,sets bit1 in record+124. Otherwise no work. Returns record pointer. Assembly pushes four arguments to0x559A30 despite incomplete decompiler call. No index-bounds or degenerate-triangle handling in this wrapper; cached flag suppresses recomputation after coordinate changes.
int __cdecl rf_renderer_cache_indexed_triangle_normal(int a1, int a2)
{
  int result; // eax

  result = a1;
  if ( (*(_DWORD *)(a1 + 124) & 1) == 0 )
  {
    rf_triangle_cross_from_three_points(
      (float *)(a1 + 96),
      (const float *)(a2 + 12 * *(_DWORD *)(a1 + 20)),
      (const float *)(a2 + 12 * *(_DWORD *)(a1 + 24)),
      (const float *)(a2 + 12 * *(_DWORD *)(a1 + 28)));
    rf_vector_normalize_reciprocal_sqrt((float *)(a1 + 96));
    *(_DWORD *)(a1 + 124) |= 1u;
    return a1;
  }
  return result;
}

