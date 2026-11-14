// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589730 rf_character_find_named_node_index
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): Case-insensitive search in three tiers: primary bone names at record+76, stride76, count+72; auxiliary binding source names via pointer at+4796+56*i, count+4792; then geometry object names from pointer chain [record+6736]->[+140]->[+4], records pointer+16,count+20,stride100. Returns tier-relative index plus preceding tier counts, or-1. Does not check geometry pointer chain for NULL or restrict input name length.
// UNREALRED VERIFIED [combat-selected-drop-resource-20261111]: Case-insensitive exact named-node search uses ordered tiers: primary bones, auxiliary bindings via source-pointer names, then geometry nodes from the selected reference mesh LOD0. FIRST match wins in tier/source order. Geometry indices are offset by both bone and auxiliary counts; a geometry ParentIndex need not identify a primary bone.
int __thiscall rf_character_find_named_node_index(const char *this, char *String1)
{
  int i; // [esp+4h] [ebp-8h]
  int j; // [esp+4h] [ebp-8h]
  int k; // [esp+4h] [ebp-8h]
  int v7; // [esp+8h] [ebp-4h]

  for ( i = 0; i < *((_DWORD *)this + 18); ++i )
  {
    if ( !_stricmp(String1, this + 76 * i + 76) )
      return i;
  }
  for ( j = 0; j < *((_DWORD *)this + 1198); ++j )
  {
    if ( !_stricmp(String1, *((const char **)this + 14 * j + 1199)) )
      return *((_DWORD *)this + 18) + j;
  }
  v7 = *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1684) + 140) + 4);
  for ( k = 0; k < *(_DWORD *)(v7 + 20); ++k )
  {
    if ( !_stricmp(String1, (const char *)(*(_DWORD *)(v7 + 16) + 100 * k)) )
      return *((_DWORD *)this + 1198) + *((_DWORD *)this + 18) + k;
  }
  return -1;
}

