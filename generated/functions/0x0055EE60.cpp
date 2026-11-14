// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055EE60 rf_packed_matrix_element_at_row16_column4_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, 48-byte layout permutations, interpolation aliasing, packed3x4 template/stack offsets and wrapped game clocks): ECX base plus signed row and column DWORDs, RET8. Returns raw pointer base+(row<<4)+(column<<2), using16byte row and4byte element. No bounds, layout or signed/overflow checks. For48byte3x4 matrix, valid rows0..2/columns0..3; row3 points OUTSIDE object, as translation builder55E9C0 actually does.
float *__thiscall rf_packed_matrix_element_at_row16_column4_unchecked(void *this, int a2, int a3)
{
  return (float *)((char *)this + 16 * a2 + 4 * a3);
}

