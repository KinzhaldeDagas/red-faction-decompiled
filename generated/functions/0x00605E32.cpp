// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605E32 __FindAndUnlinkFrame
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl caller frame-info record*, no semantic status
// result (old int type incidental). Call getptd; if record==head at PTD+98h, fetch getptd AGAIN and set returned PTD+98h=record[1], return incidental EAX second PTD pointer.
// Otherwise fetch getptd AGAIN, traverse head via node[1]. Each iteration first tests node[1]!=NULL; missing next tail-jumps noreturn inconsistency after own frame teardown. Matching
// next pointer is spliced to record[1], EAX incidentally predecessor. No head-NULL guard before dereference, ownership/membership prevalidation, clearing removed record, object
// destruction, freeing or lock. Record==NULL and head==NULL takes head path then dereferences record+4. Original CallCatchBlock caller discards return; corrected void prototype
// avoids misleading success/status interpretation.
void __cdecl _FindAndUnlinkFrame(_DWORD *a1)
{
  DWORD i; // eax

  if ( a1 == (_DWORD *)_getptd()[38] )
  {
    _getptd()[38] = a1[1];
  }
  else
  {
    for ( i = _getptd()[38]; ; i = *(_DWORD *)(i + 4) )
    {
      if ( !*(_DWORD *)(i + 4) )
        _inconsistency();
      if ( a1 == *(_DWORD **)(i + 4) )
        break;
    }
    *(_DWORD *)(i + 4) = a1[1];
  }
}

