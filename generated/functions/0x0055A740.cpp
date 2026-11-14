// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A740 rf_matrix3_copy_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): ECX destination plus source pointer, RET4. Calls no-op vector row constructors then copies exactly36 raw bytes with inline copy semantics. Returns destination bits. No validation/orthogonalization or identity fallback.
int __thiscall rf_matrix3_copy_construct(int this, const void *a2)
{
  rf_vector3_default_construct_noop((void *)this);
  rf_vector3_default_construct_noop((void *)(this + 12));
  rf_vector3_default_construct_noop((void *)(this + 24));
  qmemcpy((void *)this, a2, 0x24u);
  return this;
}

