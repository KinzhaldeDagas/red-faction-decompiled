// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F260 rf_unpaused_timestamp_arm_random_inclusive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): ECX timestamp plus minMs,maxMs, RET8. Calls rand once, computes minMs+rand()%(maxMs-minMs+1), arms through55F1F0 using UNPAUSED clock663E94. Inclusive integer range only for valid nonoverflowing bounds, modulo bias/15bit source limits remain. No divisor/order/overflow guard; return is arming helper incidental bits.
int __thiscall rf_unpaused_timestamp_arm_random_inclusive(int *this, int a2, int a3)
{
  int v3; // eax

  v3 = rand();
  return (int)rf_clock_deadline_set_wrapped_offset(this, a2 + v3 % (a3 - a2 + 1));
}

