// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004838C0 rf_vector3_add_scalar_in_place
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Thiscall vector,scalar;sequentially adds scalar to all3 components,returns receiver. Used to expand AABB maximum by sphere radius;no reorder,clamp or finite check.
float *__thiscall rf_vector3_add_scalar_in_place(float *this, float a2)
{
  *this = *this + a2;
  *(this + 1) = *(this + 1) + a2;
  *(this + 2) = *(this + 2) + a2;
  return this;
}

