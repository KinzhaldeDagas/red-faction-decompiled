// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A680 rf_vector2_add_to_output
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): ECX first two-float vector plus output and second input, RET8. Stages x/y sums before component setter, returns output. Exact input/output alias safe; no extra component access.
float *__thiscall rf_vector2_add_to_output(float *this, float *a2, float *a3)
{
  float v4; // [esp+8h] [ebp-Ch]
  float v5; // [esp+Ch] [ebp-8h]

  v5 = *(this + 1) + a3[1];
  v4 = *this + *a3;
  rf_vector2_assign_components(a2, v4, v5);
  return a2;
}

