// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00411100 rf_vector3_scale_in_place_return_self
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Thiscall vector pointer in ECX and one float scalar. Multiplies X,Y,Z in place and returns the same pointer. No finite checks, saturation or allocation. Used to apply per-axis scale to camera matrix rows.
float *__thiscall rf_vector3_scale_in_place_return_self(float *this, float a2)
{
  *this = *this * a2;
  *(this + 1) = *(this + 1) * a2;
  *(this + 2) = *(this + 2) * a2;
  return this;
}

