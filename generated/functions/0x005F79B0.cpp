// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F79B0 rf_model_geometry_destroy_lod_table
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Cdecl table pointer beginning signedDWORD LOD count,then pointers at4+4*i. Iterates i<count,passes each to0x5F7A00 conditional release,then operator delete(table). No NULL table guard,upper bound or clearing. Negative count skips entries but still deletes table. Nested release can skip ownership-flag8 or NULL-raw-data entries,so does not unconditionally free every nested header.
void __cdecl rf_model_geometry_destroy_lod_table(_DWORD *a1)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < *a1; ++i )
    rf_model_geometry_release_lod_if_owned(a1[i + 1]);
  operator delete(a1);
}

