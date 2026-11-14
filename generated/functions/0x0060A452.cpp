// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A452 __initterm
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native initializer walker uses BEGIN in EAX and ONE caller stack END pointer, not two cdecl stack pointers. Save ESI=begin; unsigned while cursor<end, load
// callbackDWORD, invoke nonNULL with NO explicit arguments, advance4; no callback status test or early stop. NULL entries skipped. End<=begin reads none. No
// array-size/alignment/ownership/overflow guard; callback may modify global state. Plain RET leaves end slot for caller cleanup. Original60A4EA/60A5EE/60A5FE callsites push end,
// setEAX begin, ADD4; corrected custom ABI.
void __usercall _initterm(void *first@<eax>, void *last)
{
  while ( first < last )
  {
    if ( *(_DWORD *)first )
      (*(void (**)(void))first)();
    first = (char *)first + 4;
  }
}

