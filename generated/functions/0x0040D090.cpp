// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D090 rf_vector_multiply_scalar
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Verified thiscall: ECX const input vec3,first stack output vec3,second float scalar,RET8; returns output POINTER EAX. Computes three float-rounded products before output setter; alias with input supported. No input mutation except alias,allocation,length scaling rule or normalization. Corrected old int return/output types; EAX is caller result vector,not a numeric float/scalar.
float *__thiscall rf_vector_multiply_scalar(const float *vector, float *scaled_result, float scalar)
{
  float v4; // [esp+Ch] [ebp-10h]
  float v5; // [esp+10h] [ebp-Ch]
  float v6; // [esp+14h] [ebp-8h]

  v6 = *(vector + 2) * scalar;
  v5 = *(vector + 1) * scalar;
  v4 = *vector * scalar;
  rf_vector3_set_components_return_destination(scaled_result, v4, v5, v6);
  return scaled_result;
}

