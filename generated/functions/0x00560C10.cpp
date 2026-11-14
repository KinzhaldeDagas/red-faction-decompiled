// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00560C10 rf_string_greater_string_case_insensitive
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, string ownership/extent layout and branch conditions): Recovered cdecl comparison of two RF string objects. If both stored extents are zero returns 0. If both extents are nonzero, returns _stricmp(left.buffer,right.buffer) > 0. Otherwise returns rightExtent==0. Uses stored extents, not strlen/is_empty; assumes non-NULL object pointers and buffers for nonzero extents. Does not mutate inputs; bool result is AL.
bool __cdecl rf_string_greater_string_case_insensitive(const void *a1, const void *a2)
{
  if ( !*(_DWORD *)a1 && !*(_DWORD *)a2 )
    return 0;
  if ( *(_DWORD *)a1 && *(_DWORD *)a2 )
    return _stricmp(*((const char **)a1 + 1), *((const char **)a2 + 1)) > 0;
  return *(_DWORD *)a2 == 0;
}

