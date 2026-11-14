// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004420A0 rf_player_build_referenced_object_controls
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): One cdecl required player pointer; no uniform success return, forwards full4414D0 EAX. Read wrapper POINTER
// DWORD[player+196], then referenced object POINTER DWORD[wrapper+0]. Form output ADDRESS=referencedObject+1800 (0x708), push that ADDRESS and original player to4414D0. This is
// address arithmetic on the first wrapped pointer, NOT loading a control pointer at object+1800. No player/wrapper/referenced-object NULL or runtime-type check: null referenced
// object would form nonnull address0x708. Pause/client gating and all control-output/return behavior belong to4414D0; no own state writes.
int __cdecl rf_player_build_referenced_object_controls(int a1)
{
  return rf_player_build_controls_unpaused_unblocked(a1, **(_DWORD **)(a1 + 196) + 1800);
}

