// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006154E2 __seh_longjmp_unwind4@4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Stdcall context pointer,RET4. Save currentEBP,setEBP=contextDWORD0. Cdecl local_unwind4(context+40 DWORD,context+24 DWORD,context+28 DWORD),ordered by three
// native pushes,ADD12. Restore previousEBP and return rawdelegateEAX. No own NULL/bounds/security-cookie check or context reset; helper interprets raw fields and performs unwind.
void __stdcall _seh_longjmp_unwind4(int a1)
{
  _local_unwind4(*(void **)a1, *(const unsigned int **)(a1 + 40), *(_DWORD **)(a1 + 24), *(_DWORD *)(a1 + 28));
}

