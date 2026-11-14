// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00412280 rf_camera_slot_set_state5
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): One cdecl slot pointer. Unconditionally writes only DWORD slot+8=EXACT5 and returns canonicalAL1. No slot NULL test,
// camera/player read, target resolve, transform/clock operation or state prerequisite. UpperEAX bits incidental; numeric state setter does not itself perform the state5 frame
// behavior.
char __cdecl rf_camera_slot_set_state5(int a1)
{
  *(_DWORD *)(a1 + 8) = 5;
  return 1;
}

