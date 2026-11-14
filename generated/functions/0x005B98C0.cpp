// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B98C0 rf_mesh_find_hierarchy_node_name_prefix
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): ECX mesh record plus name, RET4. NULL name or DWORD72==0 returns-1. Follows pointer76->offset140->offset4 to hierarchy record, loops hierarchy count20 over100byte records from16, comparing _strnicmp(recordStart,name,strlen(name)). Returns FIRST case-insensitive prefix match; empty supplied name matches first existing record. No full-equality requirement or pointer-chain validation.
// UNREALRED VERIFIED [combat-selected-drop-resource-20261111]: Static named-node lookup uses the FIRST mesh record and its LODtable+4 first-LOD descriptor. Returns the FIRST case-insensitive PREFIX match using strlen(request): grip_1 can match grip_10. This differs from character exact lookup and an all-MSUB render-prop search.
int __thiscall rf_mesh_find_hierarchy_node_name_prefix(_DWORD *this, char *String2)
{
  int i; // [esp+14h] [ebp-8h]
  int v4; // [esp+18h] [ebp-4h]

  if ( !String2 )
    return -1;
  if ( !*(this + 18) )
    return -1;
  v4 = *(_DWORD *)(*(_DWORD *)(*(this + 19) + 140) + 4);
  for ( i = 0; i < *(_DWORD *)(v4 + 20); ++i )
  {
    if ( !_strnicmp((const char *)(*(_DWORD *)(v4 + 16) + 100 * i), String2, strlen(String2)) )
      return i;
  }
  return -1;
}

