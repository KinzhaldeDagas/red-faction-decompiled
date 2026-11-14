// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060E669 ___TypeMatch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(const HandlerType*,const CatchableType*,const
// ThrowInfo*), Boolean EAX exactly0/1. Load handler.pType at+4. NULL descriptor OR descriptor byte+8 NUL ->return1 immediately, WITHOUT reading catchable/throwInfo or enforcing
// qualifier/property bits (catch-all path). Otherwise load catchable.pType at+4; equal descriptor pointers skip string compare; unequal compare NUL-terminated decorated names at
// descriptor+8 through strcmp, nonzero ->0. Pointer identity and exact case-sensitive byte names accepted; no demangling or base traversal here. Then if catchable properties BYTE0
// mask2 set require handler adjectives BYTE0 mask8; if ThrowInfo attributes DWORD0 mask1 require handler mask1; attributes mask2 require handler mask2. All satisfied ->1. Other bits
// ignored. No NULL catchable/throwInfo/descriptor validation on named path, record length, destination binding, object construction, RTTI lookup, locking or allocation. Preserve
// ESI/EDI. Existing HandlerType,CatchableType,ThrowInfo layouts verified; replace raw-int/unnamed-DWORD arguments with these existing const types, no new local types.
BOOL __cdecl __TypeMatch(const HandlerType *a1, const CatchableType *a2, const ThrowInfo *a3)
{
  const struct TypeDescriptor *pType; // eax
  TypeDescriptor *v4; // ecx
  BOOL result; // eax

  pType = a1->pType;
  result = true;
  if ( pType && pType->name[0] )
  {
    v4 = a2->pType;
    if ( pType != v4 )
    {
      if ( strcmp(pType->name, v4->name) )
        return false;
    }
    if ( (a2->properties & 2) != 0 && (a1->adjectives & 8) == 0
      || (a3->attributes & 1) != 0 && (a1->adjectives & 1) == 0
      || (a3->attributes & 2) != 0 && (a1->adjectives & 2) == 0 )
    {
      return false;
    }
  }
  return result;
}

