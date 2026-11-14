// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BCCB0 rf_object_copy_entity_vector7D4_or_position
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, object room/attachment ownership, shape-based ground lighting, native dispatcher table and resolver/view distinctions): Cdecl(common,outVec3). NULL common returns AL0 without writing output. Nonnull type0 whose HANDLE44 resolves via entity resolver433EE0 copies resolved entity vector+2004 (0x7D4); other object types or failed entity resolve copy input common position+60. Returns AL1 on all nonnull paths, not the copy helper result. Meaning of Entity7D4 is not inferred as generic eye/forward/physics position. No destination null guard or finite check.
char __cdecl rf_object_copy_entity_vector7D4_or_position(int a1, float *destination)
{
  float v3[3]; // [esp+0h] [ebp-1Ch] BYREF
  float copy_result[3]; // [esp+Ch] [ebp-10h] BYREF
  int v5; // [esp+18h] [ebp-4h]

  if ( !a1 )
    return 0;
  if ( *(_DWORD *)(a1 + 36) || (v5 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 44))) == 0 )
  {
    rf_vector_copy(destination, v3, (const float *)(a1 + 60));
    return 1;
  }
  else
  {
    rf_vector_copy(destination, copy_result, (const float *)(v5 + 2004));
    return 1;
  }
}

