// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055A710 rf_matrix3_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, triangle fan geometry, x87 returns, matrix construction/extraction, vector aliasing and receiver/stack ABI): Calls no-op vector default constructor on rows0,12,24 and returns receiver. Writes NO matrix components. Does not initialize identity/zero; storage remains as supplied.
char *__thiscall rf_matrix3_construct(char *this)
{
  rf_vector3_default_construct_noop(this);
  rf_vector3_default_construct_noop(this + 12);
  rf_vector3_default_construct_noop(this + 24);
  return this;
}

