// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A46F __initterm_e
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl two pointer bounds. EAX status starts0; unsigned scan first..<last. Before each element stop if prior callback result!=0. NonNULL callback invoked with
// no explicit args, rawEAX retained; NULL slot preserves prior0. Pointer advances4 even after nonzero callback, then exits before next callback. Return0 empty/all skipped/all zero,
// else first nonzero status. No NULL array/capacity/alignment/overflow guard.
int __cdecl _initterm_e(_PIFV *First, _PIFV *Last)
{
  int result; // eax

  result = 0;
  while ( First < Last && !result )
  {
    if ( *First )
      result = (*First)();
    ++First;
  }
  return result;
}

