// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ACB70 rf_multiplayer_store_powerup_state_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl BYTE argument. Copy lowBYTE to global662C28 and return same AL. No masking, normalization, guard or other mutation. Meaning beyond this shared powerup-state
// storage is not established.
char __cdecl rf_multiplayer_store_powerup_state_byte(char a1)
{
  byte_662C28 = a1;
  return a1;
}

