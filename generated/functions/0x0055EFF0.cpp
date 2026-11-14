// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EFF0 rf_timestamp_arm_random_inclusive_milliseconds
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): ECX timestamp plus minMs,maxMs, RET8. Calls CRT rand ONCE and arms game-clock deadline through55EF80 with minMs + rand() % (maxMs-minMs+1). Inclusive integer upper bound for valid arithmetic, modulo-biased15bit randomness; large intervals may not be fully reachable. No ordering/divisor/overflow checks: reversed/overflowing bounds can yield invalid modulo or divide fault. Return inherits arming helper mixed incidental pointer/integer bits.
// UNREALRED VERIFIED [combat-native-ai-dependencies-20261111] One shared CRT rand15 draw BEFORE wrapped32 width=max-min+1, CDQ/IDIV signed width, then wrapped32 min+remainder and55EF80 Arm. Equal bounds still draw; negative nonzero divisor is not normalized; zero width faults AFTER draw. Host fallible sampler preserves draw/output boundary and reports this unsupported fault rather than inventing a duration. Freshprobe2 55EFF7..55F00F.
int *__thiscall rf_timestamp_arm_random_inclusive_milliseconds(int *this, int a2, int a3)
{
  int v3; // eax

  v3 = rand();
  return rf_replicator_arm_milliseconds(this, a2 + v3 % (a3 - a2 + 1));
}

