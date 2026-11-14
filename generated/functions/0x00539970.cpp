// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539970 rf_uv_scroll_descriptor_set_velocity
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Thiscall descriptor,velocityU,velocityV. Writes float+4/+8,returns receiver. Key DWORD0 and cached face array+12 unchanged;no face UV updates,normalization or packet invalidation.
float *__thiscall rf_uv_scroll_descriptor_set_velocity(float *this, float a2, float a3)
{
  *(this + 1) = a2;
  *(this + 2) = a3;
  return this;
}

