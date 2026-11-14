// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C6F0 rf_entity_set_state814_mask80000
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl entity. Unconditionally OR DWORD2068 with80000; return original entity pointer in EAX. No sounds, guards, list/timer work or other stores.
int __cdecl rf_entity_set_state814_mask80000(int a1)
{
  *(_DWORD *)(a1 + 2068) |= 0x80000u;
  return a1;
}

