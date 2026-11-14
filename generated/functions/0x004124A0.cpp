// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004124A0 rf_camera_slot_has_player_unchecked
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): One cdecl 32-bit slot index. Native IMUL12 computes wrapping byte offset, reads DWORD[666AA4+offset], returns canonicalAL1 iff
// nonzero elseAL0. 666AA4 is player field of12-byte camera-slot records. No bounds/sign check, two-slot limit, camera-pointer check or player-handle resolution. Other EAX bits retain
// incidental index/product data; bool result is AL.
bool __cdecl rf_camera_slot_has_player_unchecked(int a1)
{
  return unk_666AA4[3 * a1] != 0;
}

