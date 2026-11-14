// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BFD50 rf_collision_remove_pairs_for_object
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Cdecl raw object pointer. Walks active pair header813BD0, caching each next DWORD BEFORE list removal/recycling. Matches pointer equality in pair+4 or+8, removes using previous-node helper or head/search helper, then prepends record to free header813C18; previous advances only for retained records. Object fields/flags payload+4/+8/+12 remain stale in recycled node. No object deletion, UID resolution, duplicate check or normalized status; return is incidental last node/list-helper bits. No null/list/concurrent mutation guards.
_DWORD *__cdecl rf_collision_remove_pairs_for_object(int a1)
{
  _DWORD *result; // eax
  int next_stdcall; // [esp+0h] [ebp-Ch]
  _DWORD *v3; // [esp+4h] [ebp-8h]
  _DWORD *v4; // [esp+8h] [ebp-4h]

  result = (_DWORD *)rf_receiver_get_first_dword(dword_813BD0);
  v3 = result;
  v4 = nullptr;
  while ( v3 )
  {
    next_stdcall = rf_intrusive_node_get_next_stdcall((int)v3);
    if ( v3[1] == a1 || v3[2] == a1 )
    {
      if ( v4 )
        rf_intrusive_slist_remove_with_previous(dword_813BD0, v3, v4);
      else
        rf_intrusive_slist_remove_search_unchecked_count(dword_813BD0, v3);
      result = rf_intrusive_slist_push_front(dword_813C18, v3);
    }
    else
    {
      result = v3;
      v4 = v3;
    }
    v3 = (_DWORD *)next_stdcall;
  }
  return result;
}

