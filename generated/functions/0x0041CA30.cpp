// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CA30 rf_vector3_components_not_equal
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): thiscall comparison: returns true if any of the three float components compares unequal. Uses exact floating comparisons, with no epsilon. NaN components compare unequal. Used to detect changes from previous emitter position.
bool __thiscall rf_vector3_components_not_equal(float *this, float *a2)
{
  return *a2 != *this || a2[1] != *(this + 1) || a2[2] != *(this + 2);
}

