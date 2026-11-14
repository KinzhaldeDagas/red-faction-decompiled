// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D570 rf_vector_negate
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Thiscall ECX source receiver, one stack outVector, RET4. Loads components in Z,Y,X order, FCHS each, stores
// four-byte scalar stack slots; only then calls setter ECX=out, stack(x,y,z). Returns out pointerEAX. Source/output ordinary overlap safe because all source loads precede destination
// writes; no normalization, clamp or zero/finite admission. Uses floating sign-change instructions rather than integer bitwise XOR.
float *__thiscall rf_vector_negate(float *this, float *a2)
{
  float v3; // [esp+0h] [ebp-10h]
  float v4; // [esp+4h] [ebp-Ch]
  float v5; // [esp+8h] [ebp-8h]

  v5 = -*(this + 2);
  v4 = -*(this + 1);
  v3 = -*this;
  rf_vector3_set_components_return_destination(a2, v3, v4, v5);
  return a2;
}

