// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539AE0 rf_uv_scroll_descriptor_contains_cached_face
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Recovered thiscall descriptor,face pointer. Linear search member pointer-array+12,returns AL1 on pointer equality,0 if absent. Requeries array count each iteration;no face field comparison,allocation or cache rebuild. Bounds539AE0..539B2F already code in original database.
unsigned __int8 __thiscall rf_uv_scroll_descriptor_contains_cached_face(const void *this, const void *a2)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((char *)this + 12); ++i )
  {
    if ( a2 == *(const void **)sub_552200((_DWORD *)this + 3, i) )
      return 1;
  }
  return 0;
}

