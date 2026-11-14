// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041BAD0 rf_glare_mark_delete_if_owner_missing
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl glare. If common owner handle+48==-1, returns original glare bits unchanged. Otherwise resolves owner; success returns owner pointer bits without mutation, failure ORs common flags+124 mask2 (deferred-delete flag) and returns glare bits. No immediate unlink/free, owner reassignment or clearing of an existing delete mark; return is not uniform bool/status.
int __cdecl rf_glare_mark_delete_if_owner_missing(int a1)
{
  int result; // eax

  result = a1;
  if ( *(_DWORD *)(a1 + 48) != -1 )
  {
    result = rf_object_resolve_handle(*(_DWORD *)(a1 + 48));
    if ( !result )
    {
      *(_DWORD *)(a1 + 124) |= 2u;
      return a1;
    }
  }
  return result;
}

