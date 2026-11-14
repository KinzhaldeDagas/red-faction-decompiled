// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00567F20 rf_float_cell_assign_return_self
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, signed pool divisions, lookup-table floating arithmetic, RNG trial counts, formatting and strict epsilon predicates): ECX pointer to one float plus by-value float,RET4. Stores scalar at receiver0 and returns receiver. No validation,reference counting,arithmetic or additional fields.
float *__thiscall rf_float_cell_assign_return_self(float *self, float value)
{
  *self = value;
  return self;
}

