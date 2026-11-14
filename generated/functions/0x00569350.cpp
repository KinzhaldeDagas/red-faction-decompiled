// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569350 rf_record_vector_at24_default_construct_noop
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): ECX receiver; calls vector no-op constructor at receiver+24 and returns receiver. This callee writes no vector bytes; therefore no record field is initialized by this wrapper. No evidence for additional semantic class role.
char *__thiscall rf_record_vector_at24_default_construct_noop(char *this)
{
  rf_vector3_default_construct_noop(this + 24);
  return this;
}

