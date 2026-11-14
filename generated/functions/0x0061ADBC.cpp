// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061ADBC __un_inc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl character,stream. Character==-1 exits with incomingEAX UNASSIGNED, not guaranteedEOF/zero. Every other character tears down empty frame and TAIL JMP
// ungetc_nolock with originaltwo stack slots; result delegated. No own buffer/count mutation, lock or errno handling.
int __cdecl _un_inc(int Character, FILE *Stream)
{
  int result; // eax

  if ( Character != -1 )
    return _ungetc_nolock(Character, Stream);
  return result;
}

