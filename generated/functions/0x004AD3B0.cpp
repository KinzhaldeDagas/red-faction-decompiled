// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AD3B0 rf_powerup_has_player_kind
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Cdecl(player,kind) wrapper for4ACC70 with outNode=NULL. Returns native AL membership; does not check expiration or consult entity flags. No additional validation or
// mutation.
char __cdecl rf_powerup_has_player_kind(int a1, int a2)
{
  return rf_powerup_node_find_player_kind(a1, a2, nullptr);
}

