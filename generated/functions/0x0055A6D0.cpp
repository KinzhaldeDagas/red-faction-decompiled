// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A6D0 rf_vector2_scale_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): cdecl(output,scalar,input). Stages input x/y times scalar before stores, returns output. Exact input/output alias safe; no normalization or finite checks.
float *__cdecl rf_vector2_scale_to_output(float *a1, float a2, float *a3)
{
  float v4; // [esp+8h] [ebp-8h]
  float v5; // [esp+Ch] [ebp-4h]

  v5 = a3[1] * a2;
  v4 = *a3 * a2;
  rf_vector2_assign_components(a1, v4, v5);
  return a1;
}

