// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B7B0 rf_ai_accumulate_normalized_world_vector
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): Cdecl(required AI block,INOUT vector pointer,scalar float). Normalizes caller vector IN PLACE via reciprocal-sqrt normalizer, scales
// normalized vector into local output, then accumulates it into block vector+1280. Input is mutated independently of accumulated result. No own zero/finite guard, clamping, matrix
// transform or clearing of prior accumulation. EAX is accumulate-helper result.
float *__cdecl rf_ai_accumulate_normalized_world_vector(int a1, float *vector, float scalar)
{
  float *v3; // eax
  float scaled_result[3]; // [esp+4h] [ebp-Ch] BYREF

  rf_vector_normalize_reciprocal_sqrt(vector);
  v3 = rf_vector_multiply_scalar(vector, scaled_result, scalar);
  return rf_vector_accumulate((float *)(a1 + 1280), v3);
}

