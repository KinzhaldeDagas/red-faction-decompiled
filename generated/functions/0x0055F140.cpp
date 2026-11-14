// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F140 rf_timestamp_signed_elapsed_milliseconds
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): ECX4byte game-clock timestamp. Returns NEGATION of signed remaining55F0B0; can be negative for future deadlines. Unarmed negative timestamp yields-1072800000, not0 or invalid-status boolean. Does not reset or query a separate clock.
int __thiscall rf_timestamp_signed_elapsed_milliseconds(int *this)
{
  return -rf_replicator_signed_remaining_milliseconds(this);
}

