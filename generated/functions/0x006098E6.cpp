// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006098E6 _fflush
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Public fflush. NULL callsflsall(0) without individualFILElock. NonNULL
// lock_file/armSEH/callfflush_nolock/save result/finallyunlock. No own buffer reset, commit, callback, resultmapping or failure rollback beyond delegate behavior.
int __cdecl fflush(FILE *Stream)
{
  int v2; // [esp+10h] [ebp-1Ch]

  if ( !Stream )
    return flsall(0);
  _lock_file(Stream);
  v2 = _fflush_nolock(Stream);
  _unlock_file(Stream);
  return v2;
}

