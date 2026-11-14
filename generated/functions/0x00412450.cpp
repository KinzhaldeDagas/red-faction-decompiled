// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412450 rf_camera_slot_destroy_entity
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): One cdecl slot pointer. If slot DWORD0 is nonNULL, calls entity scalar-deleting destructor4124C0(this=camera,flags=1); then
// unconditionally clears slot DWORD0 and DWORD1, in order, and returns original slot pointer in EAX. Leaves state DWORD+8 unchanged. No slot NULL guard, global index reset, parent
// detach, destructor-result predicate or alternate allocation. Null camera skips destruction but still clears player pointer.
void **__cdecl rf_camera_slot_destroy_entity(void **a1)
{
  if ( *a1 )
    rf_entity_scalar_deleting_destructor(*a1, 1);
  *a1 = nullptr;
  a1[1] = nullptr;
  return a1;
}

