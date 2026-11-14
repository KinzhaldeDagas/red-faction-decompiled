// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4540 rf_player_find_by_network_id
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): Cdecl byte ID,low8 bits only;traverses head87C324 untilNULL or head-circular closure. Returns FIRST player whose byte at(player4608)+20 equals argument bits. Compiler sign-extends both bytes before equality;all256 byte patterns compare by same low-byte identity. No own player-net-data pointer/list guard,uniqueness check or mutation. Existing descriptive name/comment retained;returns playerEAX orNULL.
_DWORD *__cdecl rf_player_find_by_network_id(char a1)
{
  _DWORD *v2; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  for ( i = (_DWORD *)dword_87C324; i; i = v2 )
  {
    if ( *(char *)(i[1152] + 20) == a1 )
      return i;
    if ( *i == dword_87C324 )
      v2 = nullptr;
    else
      v2 = (_DWORD *)*i;
  }
  return nullptr;
}

