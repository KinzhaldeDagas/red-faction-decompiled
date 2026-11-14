// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567D20 rf_determinant2x2_x87
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, matrix multiplication order, degenerate basis repair, inverse behavior, scalar motion profiles and x87 intrinsic identity): cdecl(a,b,c,d) float values. Returns float-rounded a*d-c*b throughST0. No matrix pointer, normalization, finite check or mutation.
double __cdecl rf_determinant2x2_x87(float a1, float a2, float a3, float a4)
{
  return (float)(a1 * a4 - a3 * a2);
}

