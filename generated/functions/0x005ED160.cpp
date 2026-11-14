// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED160 rf_object_construct_invalid_dword_at_8
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): ECX receiver, no stack arguments, plain RET. Calls4CD390 with ECX=self+8, which writes exactly DWORD0xFFFFFFFF then returns slot address; wrapper overwrites
// EAX with original self and returns self. Does not initialize first8 bytes, install vtable, allocate, clear whole object or null-check receiver. Xref at62EAA3 is data rather than a
// decoded direct CALL; generic name reflects native behavior without asserting an original SDK class.
void *__thiscall rf_object_construct_invalid_dword_at_8(void *self)
{
  rf_dword_construct_invalid_minus_one((unsigned int *)self + 2);
  return self;
}

