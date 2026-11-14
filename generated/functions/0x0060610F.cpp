// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060610F crt_bad_alloc_destroy_members
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): ECX exception receiver, no stack args. First install std::bad_alloc vtable in receiver DWORD0, then TAIL JMP60F87E base exception destructor. Base destructor
// installs std::exception vtable and conditionally frees owned message when DWORD+8 nonzero; no containing object delete, pointer/ownership reset or own frame/return-value
// assignment. Tail transfers original caller return address. Not construction/allocation despite initial vtable write.
void __thiscall crt_bad_alloc_destroy_members(void *this)
{
  *(_DWORD *)this = &std::bad_alloc::`vftable';
  crt_exception_destroy_owned_message(this);
}

