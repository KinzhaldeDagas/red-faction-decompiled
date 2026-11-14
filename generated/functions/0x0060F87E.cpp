// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F87E crt_exception_destroy_owned_message
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native thiscall ECX exception receiver, no stack args/plain RET. FIRST CMP DWORD[self+8],0 establishes ownership test, then MOV std::exception vtable
// to[self+0] (MOV preserves ZF), JZ skip free. Nonzero fullDWORD ownership flag pushes message pointer[self+4], calls cdecl free and POP ECX reclaims slot; no nonNULL message
// precheck. Does not clear message pointer or ownership DWORD, free containing receiver, recurse virtual destructor or restore derived vtable. Repeated invocation on owned stale
// message is not guarded. Native static bad_alloc destructor62F68F supplies fixed0202133C; constructor/other callers share same base cleanup. Void contract, EAX unspecified; prior
// unnamed classification preserved.
void __thiscall crt_exception_destroy_owned_message(void *this)
{
  bool v1; // zf

  v1 = *((_DWORD *)this + 2) == 0;
  *(_DWORD *)this = &std::exception::`vftable';
  if ( !v1 )
    free(*((void **)this + 1));
}

