// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00584710 rf_float4_assign_components_return_this
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Thiscall(destination this,source float4). Copies x,y,z,w in forward scalar order,returns this;no normalization,NULL/overlap protection or allocation. Quaternion track sampler uses after packed interpolation/unpack;this is raw four-float assignment.
float *__thiscall rf_float4_assign_components_return_this(float *this, float *a2)
{
  *this = *a2;
  *(this + 1) = a2[1];
  *(this + 2) = a2[2];
  *(this + 3) = a2[3];
  return this;
}

