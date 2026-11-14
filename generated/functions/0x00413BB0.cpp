// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00413BB0 rf_callback_zero_float52_for_flag200_entity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Cdecl(opaqueFirstRecord,otherObject). If object-is-entity predicate succeeds forother AND its class660 DWORD1828 bit0x200 set,writes F32+0.0 at firstRecord52. ReturnsAL0 on EVERY path,including after mutation;not a pure boolean test/no-op failure. No NULL/type validation of firstRecord or inferred class meaning for its+52 field.
char __cdecl rf_callback_zero_float52_for_flag200_entity(int a1, int a2)
{
  if ( rf_object_is_entity(a2) && rf_entity_class_has_contact_geomod_flag200(a2) )
    *(float *)(a1 + 52) = 0.0;
  return 0;
}

