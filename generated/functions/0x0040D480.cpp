// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D480 rf_vector_accumulate
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI firing/acquisition/probe/route-point and vector arithmetic chains, independent native review and exact
// float/stack/dataflow behavior and native signed/x87/stack/callback ABI): Thiscall ECX receiver plus one source vector stack pointer, RET4. In-place additions and float32 stores
// occur sequentially X, thenY, thenZ. EAX retains receiver pointer. Unlike output-vector scale/divide helpers, does NOT snapshot all source components before first write: partial
// overlapping vectors can observe earlier receiver writes in later source reads. Exact self-alias doubles each component. No normalization, zero/finite guard, clamp,
// returned-by-value temporary or independent source mutation beyond alias effects.
float *__thiscall rf_vector_accumulate(float *this, float *a2)
{
  *this = *this + *a2;
  *(this + 1) = *(this + 1) + a2[1];
  *(this + 2) = *(this + 2) + a2[2];
  return this;
}

