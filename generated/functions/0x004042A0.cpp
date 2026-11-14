// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004042A0 rf_ai_clear_frame_control_fields
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): One required AI block. Zeroes THREE floats at+1140 and THREE at+1128 through vector helpers, then FLOAT+1156 and+1160 separately. Does not clear
// FLOAT+1152 or vector+1280 (403DE0 separately clears latter). No other mode/target/velocity/deadline mutation. Native EAX retains input block after final stores; no own null guard.
float *__cdecl rf_ai_clear_frame_control_fields(float *a1)
{
  rf_vector3_zero_return_destination(a1 + 285);
  rf_vector3_zero_return_destination(a1 + 282);
  a1[289] = 0.0;
  a1[290] = 0.0;
  return a1;
}

