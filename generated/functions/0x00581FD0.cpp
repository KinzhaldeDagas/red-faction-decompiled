// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581FD0 rf_clip_vertex_refs_apply_depth_split_outcodes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered cdecl(refArray,count,aggregate2bytes,beyondStartByte). Each refArray[i] points to an entry whose FIRST DWORD points to vertex;vertex cameraZ at+8,outcode byte+24. Clears bit01 on every vertex first. Mode18CD374==1 and z<start18CD37C sets01;otherwise z>start sets *beyondStartByte=1 and mode==2 also sets01. Equal/unordered comparisons set neither;beyondStartByte is never initialized/cleared here. Accumulates aggregate[0] OR and aggregate[1] AND with full modified vertex byte,using caller initial values. If both aggregate bytes have01 after loop,clears01 from ALL input vertices and BOTH aggregate bytes,retains all other bits and beyond flag. No pointer/count checks;count<=0 skips vertices but still examines/possibly
// clears aggregate01. Return EAX incidental,prototype void chosen because only side effects are defined;does not independently reject polygon or clip geometry.
void __cdecl rf_clip_vertex_refs_apply_depth_split_outcodes(
        void **a1,
        int a2,
        unsigned __int8 *a3,
        unsigned __int8 *a4)
{
  void *v4; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]
  int j; // [esp+4h] [ebp-4h]

  for ( i = 0; i < a2; ++i )
  {
    v4 = a1[i];
    *(_BYTE *)(*(_DWORD *)v4 + 24) &= ~1u;
    if ( dword_18CD374 == 1 && flt_18CD37C > (double)*(float *)(*(_DWORD *)v4 + 8) )
    {
      *(_BYTE *)(*(_DWORD *)v4 + 24) |= 1u;
    }
    else if ( flt_18CD37C < (double)*(float *)(*(_DWORD *)v4 + 8) )
    {
      *a4 = 1;
      if ( dword_18CD374 == 2 )
        *(_BYTE *)(*(_DWORD *)v4 + 24) |= 1u;
    }
    a3[1] &= *(_BYTE *)(*(_DWORD *)v4 + 24);
    *a3 |= *(_BYTE *)(*(_DWORD *)v4 + 24);
  }
  if ( (*a3 & 1) != 0 && (a3[1] & 1) != 0 )
  {
    for ( j = 0; j < a2; ++j )
      *(_BYTE *)(*(_DWORD *)a1[j] + 24) &= ~1u;
    a3[1] &= ~1u;
    *a3 &= ~1u;
  }
}

