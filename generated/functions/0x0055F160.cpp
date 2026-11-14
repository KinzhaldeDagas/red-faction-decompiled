// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F160 rf_timestamp_read_remaining_and_rearm
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): ECX timestamp plus binary stream, RET4. Reads signed int32 via versioned reader(stream,0,0), then arms game-clock deadline with that remaining duration. No explicit stream-status check and no unarmed sentinel handling. Writer55F190 serializes unarmed as full period1072800000; reloading that produces an ARMED deadline at current clock (or exact period boundary), losing unarmed state. Does not deserialize an absolute native timestamp.
int __thiscall rf_timestamp_read_remaining_and_rearm(int *this, void *a2)
{
  int int32_versioned; // eax

  int32_versioned = rf_binary_stream_read_int32_versioned(a2, 0, 0);
  return (int)rf_replicator_arm_milliseconds(this, int32_versioned);
}

