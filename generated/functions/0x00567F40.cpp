// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567F40 rf_float_cell_get_x87
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): ECX one-float receiver,no stack arguments. Loads stored float directly toST0 and returns as saved double;no conversion arithmetic,finite check or mutation.
double __thiscall rf_float_cell_get_x87(const float *self)
{
  return *self;
}

