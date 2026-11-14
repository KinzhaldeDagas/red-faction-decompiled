// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AD550 rf_powerup_node_construct_deadline_only
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native packet19 registry/codec, x87 quantization, powerup linked nodes, entity state masks and action
// arbitration): Thiscall(receiver20-byte node), no stack args. Construct invalid timestamp at receiver+8 then return receiver. Player0,kind4,next12,prev16 are
// untouched/uninitialized; no list insertion, allocation, entity flags or cleanup.
int *__thiscall rf_powerup_node_construct_deadline_only(int *this)
{
  rf_timestamp4_construct_invalid(this + 2);
  return this;
}

