// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561FA0 rf_model_handle_find_node_by_name
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Tag2 delegates character definition8 named-node search. Tag1 delegates5B98C0(instance4,name), which uses case-insensitive PREFIX comparison against hierarchy names with supplied name length. Tag3 loops flattened object count and compares record-base names via _stricmp exact equality, returning FIRST match; other tags/no match-1. No common null guard:tag1 helper rejects null,tag3 direct _stricmp can fault. Search semantics differ by tag.
int __thiscall rf_model_handle_find_node_by_name(_DWORD *this, char *String2)
{
  char *String1; // [esp+4h] [ebp-Ch]
  int i; // [esp+8h] [ebp-8h]
  int node_count; // [esp+Ch] [ebp-4h]

  if ( *this == 2 )
    return rf_character_find_named_node_index((const char *)*(this + 2), String2);
  if ( *this == 1 )
    return rf_mesh_find_hierarchy_node_name_prefix((_DWORD *)*(this + 1), String2);
  if ( *this != 3 )
    return -1;
  node_count = rf_model_handle_get_node_count(this);
  for ( i = 0; i < node_count; ++i )
  {
    String1 = (char *)rf_model_handle_get_indexed_record_base(this, i);
    if ( !_stricmp(String1, String2) )
      return i;
  }
  return -1;
}

