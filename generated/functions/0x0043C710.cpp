// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043C710 rf_entity_clear_state814_mask80000
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl entity. Unconditionally AND DWORD2068 withFFF7FFFF to clear80000; return original entity pointer in EAX. No sounds, guards, list/timer work or other stores.
int __cdecl rf_entity_clear_state814_mask80000(int a1)
{
  *(_DWORD *)(a1 + 2068) &= ~0x80000u;
  return a1;
}

