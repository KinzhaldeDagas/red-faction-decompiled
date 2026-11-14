// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B44D0 rf_player_find_by_network_endpoint
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): Cdecl endpoint pointer. Traverses head87C324 player list,stoppingNULL or next==globalhead. Returns FIRST player for which network_compare_endpoints(player4608,argument,1)==0. Zero comparator result means match;third argument1 controls comparison perdelegate. NULLhead->NULL;no own player-net-data,NULLendpoint or corrupted-list guard,allocation or mutation. Returns player pointerEAX orNULL.
_DWORD *__cdecl rf_player_find_by_network_endpoint(int a1)
{
  _DWORD *v2; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  for ( i = (_DWORD *)dword_87C324; i; i = v2 )
  {
    if ( !rf_network_compare_endpoints(i[1152], a1, 1) )
      return i;
    if ( *i == dword_87C324 )
      v2 = nullptr;
    else
      v2 = (_DWORD *)*i;
  }
  return nullptr;
}

