// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E619 crt_bad_exception_construct_from_message
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall destination plus one stack C-string pointer, RET4. LEA address of caller argument SLOT and push that pointer-to-pointer into60F7B1 std::exception
// message constructor. Save receiver ESI across delegate, install std::bad_exception vtable and return receiver. It passes address-of-slot, not message bytes as object or direct
// char** value. Base allocates/copies nonNULL message, sets ownership1 even for NULL or allocation failure; wrapper does not test failure, free prior destination, validate NULL
// receiver or allocate containing exception.
std::exception *__thiscall crt_bad_exception_construct_from_message(std::exception *this, char *a2)
{
  std::exception::exception(this, (const char **)&a2);
  *(_DWORD *)this = &std::bad_exception::`vftable';
  return this;
}

