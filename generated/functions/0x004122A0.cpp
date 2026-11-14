// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004122A0 rf_camera_slot_advance_sample_and_set_state6
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(slot pointer). Increments shared DWORD666A98 with native32-bit wrap, then compares it SIGNED against DWORD[666AD0] via
// generic first-DWORD getter486DE0; resets index to0 iff incremented index>=count. This is a single comparison/reset, not modulo or a search; negative/zero count has no separate
// guard. Afterwards sets slot DWORD+8=6 and returnsAL1. Index is global across slots, and mutation precedes slot write. No bounds/pointer validation, camera transform write,
// per-frame index progression or random draw here.
char __cdecl rf_camera_slot_advance_sample_and_set_state6(int a1)
{
  ++dword_666A98;
  if ( dword_666A98 >= rf_receiver_get_first_dword(dword_666AD0) )
    dword_666A98 = 0;
  *(_DWORD *)(a1 + 8) = 6;
  return 1;
}

