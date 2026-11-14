// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581BC0 rf_renderer_export_current_clip_planes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered cdecl(outputPlanes4f,optionalOutputTagBytes). Copies current plane data18CD3CC in source28-byte strides to destination16-byte strides,count18CD390. If tag output nonNULL,copies each record tag at18CD3C8 to contiguous byte output. Returns plane count. Main plane destination mandatory for positive count;no capacity/alias checks or support-selector export. Does not transform/normalize planes or reset count.
int __cdecl rf_renderer_export_current_clip_planes(float *a1, unsigned __int8 *a2)
{
  int i; // [esp+0h] [ebp-4h]
  int j; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_18CD390; ++i )
    rf_plane_copy(&a1[4 * i], (float *)&unk_18CD3CC + 7 * i);
  if ( a2 )
  {
    for ( j = 0; j < dword_18CD390; ++j )
      a2[j] = byte_18CD3C8[28 * j];
  }
  return dword_18CD390;
}

