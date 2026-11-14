// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040CED0 rf_entity_is_crouched_state810
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl entity bool AL. Return1 iff entity nonNULL and DWORD2064 mask400 set, otherwise0. No animation/state-selector, physical-sphere, sweep or player check. Does not
// establish that a stance transition or uncrouch clearance succeeded.
bool __cdecl rf_entity_is_crouched_state810(int a1)
{
  return a1 && (*(_DWORD *)(a1 + 2064) & 0x400) != 0;
}

