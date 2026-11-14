// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00438090 rf_entity_runtime_enabled_or_resolved_attachment
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native motion dispatch, buffered pose consumers, contact effects, selector filtering and x87 unordered branches): Cdecl(entity,key). NULLentity returnsfalse. key==-1 OR class-authored-jeep predicate false ->returns runtime DWORD2064 bit0x10000. Authored jeep and other key:scans pointer array entity2252,count at+0,base at+8,stride4;compares EACH pointee DWORD0 with key and retains LAST matching index (no break). No match ->false;last match ->resolves pointeeDWORD4 as entity UID and returns nonNULL. Does NOT fall back to runtime flag when key absent/unresolved. Negative count skips loop;array element/pointee/descriptor pointers unchecked. No mutation;AL boolean. Existing broader comment preserved;does not assign an unproven single gameplay meaning to runtime bit.
bool __cdecl rf_entity_runtime_enabled_or_resolved_attachment(int a1, int a2)
{
  int v3; // eax
  int v4; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  if ( !a1 )
    return 0;
  if ( a2 == -1 || !rf_entity_has_jeep_flag(a1) )
    return (*(_DWORD *)(a1 + 2064) & 0x10000) != 0;
  v4 = -1;
  for ( i = 0; i < rf_receiver_get_first_dword((void *)(a1 + 2252)); ++i )
  {
    if ( **(_DWORD **)sub_552200((_DWORD *)(a1 + 2252), i) == a2 )
      v4 = i;
  }
  if ( v4 < 0 )
    return 0;
  v3 = sub_552200((_DWORD *)(a1 + 2252), v4);
  return rf_entity_resolve_handle(*(_DWORD *)(*(_DWORD *)v3 + 4)) != 0;
}

