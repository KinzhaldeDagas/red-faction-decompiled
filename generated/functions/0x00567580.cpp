// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567580 rf_sqrt_fast_lookup_unchecked
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): stdcall one float bit word,RET4. Returns float bits from table1806938[index] OR (((inputExponentBits+3F800000)>>1)&7F800000),index=(bits>>14)&1023. No refinement,sign handling,zero/subnormal/NaN/Inf special case or implicit initialization. Bit manipulations are retail32bit arithmetic; not standard sqrt semantics for all inputs.
double __stdcall rf_sqrt_fast_lookup_unchecked(float x)
{
  return COERCE_FLOAT(dword_1806938[(LODWORD(x) >> 14) & 0x3FF] | (((LODWORD(x) & 0x7F800000u) + 1065353216) >> 1)
                                                                & 0x7F800000);
}

