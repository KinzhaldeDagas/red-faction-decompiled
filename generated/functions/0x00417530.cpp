// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417530 rf_clutter_skin_array_construct_capacity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Thiscall constructor delegates to 0x4175A0 and returns the receiver. Requested capacity is one DWORD, callee pops 4. Zero capacity leaves an empty header; nonzero capacity invokes the cookie-based 108-byte-record allocator. Does not preserve or release prior storage.
char *__thiscall rf_clutter_skin_array_construct_capacity(char *this, int a2)
{
  rf_clutter_skin_array_initialize_capacity(this, a2);
  return this;
}

