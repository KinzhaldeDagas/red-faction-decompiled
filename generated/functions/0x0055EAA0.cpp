// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EAA0 rf_asin_float_x87_intrinsic
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): cdecl float argument loaded intoST0, calls __CIasin, fstp to float local then fld reload, returning float-rounded arcsine throughST0 as saved double. No range clamping or special handling in wrapper. Used by orientation controller55D230 after cross-length upper clamp.
double __cdecl rf_asin_float_x87_intrinsic(float a1)
{
  return (float)asin(a1);
}

