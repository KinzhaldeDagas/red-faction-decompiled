// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005917A0 rf_log_float_via_x87_intrinsic
// UNREALRED VERIFIED [dsound-creation-20261028]: Loads caller float, invokes natural-log intrinsic, stores32-bit float then reloads x87 return. Unlike earlier falsely named log wrappers0x43C8B0, this body actually computes log. No domain/finite validation. Wrapper0x591780 retains its correct library name.
double __cdecl rf_log_float_via_x87_intrinsic(float a1)
{
  return (float)log(a1);
}

