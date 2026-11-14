// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C8750 rf_clip_polygon_extended_uv_outcode_planes
// UNREALRED VERIFIED [face-batch-20261028]: Iterates bit1,2,4,8,16,32,64. For each bit present in combined outcode*a4,calls0x5C84F0 with current/temp vertex-pointer arrays,count and flags; stores returned count. If adjacent rejected byte a4[1]set,returns temporary array immediately; otherwise swaps arrays and continues. Returns current array. Does not process outcode0x80 or itself reject count<3. Used by132-byte extended UV vertices; per-plane interpolation/allocation policy belongs to0x5C84F0,not inferred here.
_DWORD *__cdecl rf_clip_polygon_extended_uv_outcode_planes(_DWORD *a1, _DWORD *a2, int *a3, _BYTE *a4, char a5)
{
  int i; // [esp+0h] [ebp-8h]
  _DWORD *v7; // [esp+4h] [ebp-4h]

  for ( i = 1; i <= 64; i *= 2 )
  {
    if ( ((unsigned __int8)i & *a4) != 0 )
    {
      *a3 = rf_clip_polygon_extended_uv_one_plane(i, a1, (int)a2, a3, a4, a5);
      if ( a4[1] )
        return a2;
      v7 = a1;
      a1 = a2;
      a2 = v7;
    }
  }
  return a1;
}

