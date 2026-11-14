// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D030 rf_vector_add
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Verified thiscall: ECX const left vec3,first stack output vec3,second const right vec3,RET8; returns output pointer EAX. Computes all three component sums with32-bit float stores before output setter,so output may alias either input. Does not accumulate into left,allocate,normalize or return scalar. Corrected integer return/output inference for model geometry interpolation and other callers.
float *__thiscall rf_vector_add(const float *lhs, float *sum_result, const float *rhs)
{
  float v4; // [esp+Ch] [ebp-10h]
  float v5; // [esp+10h] [ebp-Ch]
  float v6; // [esp+14h] [ebp-8h]

  v6 = *(lhs + 2) + rhs[2];
  v5 = *(lhs + 1) + rhs[1];
  v4 = *lhs + *rhs;
  rf_vector3_set_components_return_destination(sum_result, v4, v5, v6);
  return sum_result;
}

