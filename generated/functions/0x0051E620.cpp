// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051E620 rf_solid_reset_array168_cache_indices
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, plane splits,intrusive face lists,room/portal visibility,clip apertures and decal submission,original ECX/stack flow and PE bytes): Thiscall solid no stack args. Signed loop from0 while i<count of pointer array at byte168, reload count each iteration; for each element write DWORD140=-1 thenDWORD144=-1. No other object/global changes, no null checks. Returns final array count viaEAX, not bool. Monitor render caller418148 runs this after backbuffer capture. Offsets are verified; subtype meaning of these two cache slots remains unassigned.
int __thiscall rf_solid_reset_array168_cache_indices(int this)
{
  int result; // eax
  int v2; // eax
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 168));
    if ( i >= result )
      break;
    v2 = *(_DWORD *)sub_552200((_DWORD *)(this + 168), i);
    *(_DWORD *)(v2 + 140) = -1;
    *(_DWORD *)(v2 + 144) = -1;
  }
  return result;
}

