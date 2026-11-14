// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C86D0 rf_clip_polygon_outcode_planes_48
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, complete skinned draw path, clipping control flow, buffer limits, original x87/integer operations and caller arguments): Cdecl input vertex-pointer array,output scratch pointer array,in/out signed count pointer,two BYTE outcodes(OR at0,AND at1),attribute mask. Returns POINTER to final vertex-pointer array in EAX despite existing int declaration. Iterates plane bits1,2,4,8,10h,20h,40h in ascending order,calling5C82E0 only when current OR contains bit. Writes returned count to *count. If output AND nonzero returns current output array immediately; otherwise swaps input/output arrays after each executed plane. Returns current input array after last plane,including unchanged input when no selected bit. Bit80h is never processed. Forwards attribute mask unchanged; no clipping arithmetic here. Arrays are both mutable because
// one-plane helper appends closure pointers to its input. No pointer/count/array-capacity/alias check,allocation/reset,zero-count early return or AND initialization in wrapper; these depend on caller/one-plane helper. Existing int/pointer-shaped arguments have32-bit ABI; this analysis leaves stored prototype unchanged.
_DWORD *__cdecl rf_clip_polygon_outcode_planes_48(_DWORD *a1, _DWORD *a2, int *a3, _BYTE *a4, char a5)
{
  int i; // [esp+0h] [ebp-8h]
  _DWORD *v7; // [esp+4h] [ebp-4h]

  for ( i = 1; i <= 64; i *= 2 )
  {
    if ( ((unsigned __int8)i & *a4) != 0 )
    {
      *a3 = rf_clip_polygon_one_plane_48(i, a1, (int)a2, a3, a4, a5);
      if ( a4[1] )
        return a2;
      v7 = a1;
      a1 = a2;
      a2 = v7;
    }
  }
  return a1;
}

