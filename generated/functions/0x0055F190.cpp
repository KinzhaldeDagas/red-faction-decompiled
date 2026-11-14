// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F190 rf_timestamp_write_signed_remaining
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): ECX timestamp plus binary stream, RET4. Computes signed remaining milliseconds55F0B0 and writes host-order int32 via stream helper. Expired durations can be negative, and unarmed timestamps serialize full period1072800000. No separate armed flag or absolute clock epoch. Returns writer result bits.
int __thiscall rf_timestamp_write_signed_remaining(const int *this, void *a2)
{
  int v2; // eax

  v2 = rf_replicator_signed_remaining_milliseconds((int *)this);
  return rf_binary_stream_write_int32_host_order(a2, v2);
}

