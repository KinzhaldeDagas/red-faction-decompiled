// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483900 rf_vector3_subtract_scalar_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Thiscall vector,scalar;sequentially subtracts scalar from each of3 components,returns receiver. Used to expand AABB minimum by sphere radius;negative scalar instead shrinks that side. No saturation or finite checks.
float *__thiscall rf_vector3_subtract_scalar_in_place(float *this, float a2)
{
  *this = *this - a2;
  *(this + 1) = *(this + 1) - a2;
  *(this + 2) = *(this + 2) - a2;
  return this;
}

