// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605E0B __IsExceptionObjectToBeDestroyed
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl exception-object identity DWORD. Obtain thread data, load linked head at thread+152, scan nodes next+4 untilNULL; any node DWORD0==argument returns0,
// reachingNULL returns1. No destruction, allocation, reference mutation, node/object dereference beyond two link fields or NULL-thread/cycle/corruption guard. Predicate means absence
// from tracked chain, not an owned deletion performed.
int __cdecl _IsExceptionObjectToBeDestroyed(int a1)
{
  _DWORD *i; // eax

  for ( i = (_DWORD *)_getptd()[38]; ; i = (_DWORD *)i[1] )
  {
    if ( !i )
      return 1;
    if ( *i == a1 )
      break;
  }
  return 0;
}

