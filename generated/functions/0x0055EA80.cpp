// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EA80 rf_asin_float
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): False decorated log(float) SDK identification. Wrapper forwards its single float argument to55EAA0, which calls x87 __CIasin and rounds result through stored float. Returns ST0 floating result, not logarithm. No explicit clamp/domain check in this wrapper.
double __cdecl rf_asin_float(float a1)
{
  return rf_asin_float_x87_intrinsic(a1);
}

