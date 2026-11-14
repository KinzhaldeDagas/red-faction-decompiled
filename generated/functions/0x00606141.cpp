// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00606141 crt_bad_alloc_copy_construct
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): ECX destination plus one stack source-exception pointer, RET4. Save destination, forward source unchanged to base std::exception copy constructor60F821, then
// overwrite destination vtable with std::bad_alloc and return destination EAX. Base copies ownership flag; borrows source message when flag0, otherwise allocates/copies nonNULL
// message, retaining NULL on allocation failure. No source/destination NULL or alias validation, old-destination cleanup, containing allocation or failure status from wrapper.
// Derived vtable installed only after base delegate returns.
std::exception *__thiscall crt_bad_alloc_copy_construct(std::exception *this, struct std::exception *a2)
{
  std::exception::exception(this, a2);
  *(_DWORD *)this = &std::bad_alloc::`vftable';
  return this;
}

