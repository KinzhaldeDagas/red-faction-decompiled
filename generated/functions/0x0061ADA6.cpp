// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061ADA6 __inc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Register FILE receiver inEDX; entryECX ignored/overwritten. DEC DWORD[stream+4] thenJS checks wrapped decrement sign. Nonnegative count: read unsignedbyte
// atcurrent pointerDWORD0,incrementpointer,return0..255. Negative result: pushstream,call filbuf,reclaim4,returnhelperEAX (mayEOF). No NULL,lock,pre-overflow/error checks; INT_MIN
// decrement wraps positive and bypasses refill. Corrected EDX-only register ABI removes fake ECX argument.
int __usercall _inc@<eax>(void *stream@<edx>)
{
  if ( --*((_DWORD *)stream + 1) < 0 )
    return _filbuf((FILE *)stream);
  return *(unsigned __int8 *)(*(_DWORD *)stream)++;
}

