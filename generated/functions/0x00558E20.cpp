// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558E20 rf_vector3_is_exact_zero
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, fields, callback paths and callers): thiscall predicate: returns true only if all three float components equal 0.0 exactly. Signed zeros pass; NaN fails. No epsilon or normalization. Used to suppress Doppler updates for a zero source velocity.
BOOL __thiscall rf_vector3_is_exact_zero(float *this)
{
  return *this == 0.0 && *(this + 1) == 0.0 && *(this + 2) == 0.0;
}

