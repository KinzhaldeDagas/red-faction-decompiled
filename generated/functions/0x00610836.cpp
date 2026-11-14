// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00610836 _write_multi_char
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): EAX points output-count/errorDWORD. Cdecl stack slots char,count,FILE*. Save counter pointerESI. While signed count>0: load FILE intoECX and char
// intoAL,decrement local count BEFORE call write_char, then stop immediately if *counter==-1; otherwise repeat. No direct fwrite/buffer loop in wrapper. Raw delegateEAX residue
// returned; if initial count<=0, EAX still incoming counter-address. No NULL/file validation or guaranteed written-character count return; callbackcount state owns failure.
_DWORD *__usercall write_multi_char@<eax>(_DWORD *result@<eax>, char a2, int a3, FILE *File)
{
  _DWORD *v4; // esi

  v4 = result;
  do
  {
    if ( a3 <= 0 )
      break;
    LOBYTE(result) = a2;
    --a3;
    result = (_DWORD *)write_char(File, (int)result, v4);
  }
  while ( *v4 != -1 );
  return result;
}

