// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591780 ?log@@YAMM@Z_9
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, tokenizer ownership/quote rules, native hook contracts, observer registration, startup signaling and thread-exit/calling-convention paths): Cdecl float argument, floating result in ST0. Pushes caller float to5917A0 and directly returns its result; underlying verified helper invokes natural-log x87 intrinsic and rounds to32-bit float before returning. No extra rounding/domain/finite check in wrapper. Existing correct decorated library log name retained, consistent with earlier5917A0 finding; this is not one of falsely identified unrelated log functions.
double __cdecl log(float a1)
{
  return rf_log_float_via_x87_intrinsic(a1);
}

