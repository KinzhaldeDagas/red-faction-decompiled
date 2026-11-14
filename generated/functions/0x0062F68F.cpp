// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062F68F crt_static_bad_alloc_destroy_0202133c
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native complete 3-instruction/20-byte body independently matched to original PE. No consumed stack arguments. Store std::bad_alloc vtable00648D58 to static
// exception object0202133C, set ECX to that SAME fixed object, TAIL JMP60F87E base std::exception message destructor. Original operator-new failure path6061A0 registers this callback
// after guarded construction of the static bad_alloc; it is not a new runtime heap allocation. Base destructor then replaces vtable with std::exception and frees owned message only
// when DWORD+8 nonzero. No containing exception allocation delete, output-pointer clearing or own return frame/normalized result. Original registration at0x006061A0.
void __cdecl crt_static_bad_alloc_destroy_0202133c()
{
  unk_202133C[0] = (int)&std::bad_alloc::`vftable';
  crt_exception_destroy_owned_message(unk_202133C);
}

