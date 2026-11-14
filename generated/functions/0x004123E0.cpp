// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004123E0 rf_camera_slot_get_room
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): One cdecl slot pointer. Reads camera=DWORD[slot], calls generic thiscall486DE0 with ECX=camera, returns its first DWORD unchanged
// in EAX. Thus this camera call path gets its cached room pointer. No slot/camera NULL check, resolver call, mutation, array indexing or camera state test.
int __cdecl rf_camera_slot_get_room(void **a1)
{
  return rf_receiver_get_first_dword(*a1);
}

