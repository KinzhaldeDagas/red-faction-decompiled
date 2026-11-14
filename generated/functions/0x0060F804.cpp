// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F804 ??0exception@std@@QAE@ABQBDH@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall exception receiver plus TWO stackDWORDs,RET8. First slot is pointer-to-message-pointer; second rawflag IGNORED. Set std::exception vtable,
// dereference first slot and BORROW that message pointer at+self4,clear ownershipDWORD+self8,return self. No strlen/malloc/copy, NULL outer-pointer validation, old-message release or
// containing-object allocation. bad_alloc default ctor supplies static-message slot and ignored1.
std::exception *__thiscall std::exception::exception(std::exception *this, const char *const *a2, int a3)
{
  std::exception *result; // eax
  int v4; // ecx

  result = this;
  *(_DWORD *)this = &std::exception::`vftable';
  v4 = (int)*a2;
  *((_DWORD *)result + 2) = 0;
  *((_DWORD *)result + 1) = v4;
  return result;
}

