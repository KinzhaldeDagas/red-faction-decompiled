// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006060F4 ??0bad_alloc@std@@QAE@XZ
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall bad_alloc default construction. Push rawflag1 and ADDRESS664BE0 (pointer-to-static-message slot) into borrowed-message exception constructor60F804;
// ECX original self savedESI. Then install bad_alloc vtable,return self. Base ignores flag slot, borrows message pointer and sets ownership0; does not allocate/copy message or self.
// No NULL receiver/constructor-result validation; this is distinct from owned message copy constructor.
std::bad_alloc *__thiscall std::bad_alloc::bad_alloc(std::bad_alloc *this)
{
  std::exception::exception(this, (const char *const *)&off_664BE0, 1);
  *(_DWORD *)this = &std::bad_alloc::`vftable';
  return this;
}

