// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006060D2 _atexit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl callback pointer, plain RET. Forward unchanged to __onexit via one stack argument; POP ECX reclaims slot after return. NEG EAX/SBB EAX,EAX/NEG EAX/DEC
// EAX maps nonNULL returned pointer to0 and NULL to-1, not the registration index or callback return. No callback invocation, NULL validation, allocator/lock/registration-list
// management or exception handling directly here: underlying onexit policy delegated. Original decorated/library identity and classification preserved.
int __cdecl atexit(void (__cdecl *Func)())
{
  return (_onexit((_onexit_t)Func) != nullptr) - 1;
}

