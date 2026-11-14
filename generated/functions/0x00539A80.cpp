// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00539A80 rf_uv_scroll_descriptor_rebuild_face_cache
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, UV descriptors and rebasing, lightmap sampling, array capacity/ownership, liquid fallback and original PE bytes): Clears count of descriptor member array+12,retains its capacity/backing. Walks solid face list at solid+112 and appends face pointers whose DWORD+56 equals descriptor key DWORD0. No velocity change,face ownership transfer,uniqueness test or stored key setter. Returns final face-list iterator result0,not cached count. No packet invalidation.
int __thiscall rf_uv_scroll_descriptor_rebuild_face_cache(_DWORD *this, int a2)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  rf_pointer_array_clear_count_keep_storage(this + 3);
  result = rf_receiver_get_first_dword((void *)(a2 + 112));
  for ( i = result; i; i = result )
  {
    if ( *(_DWORD *)(i + 56) == *this )
      rf_pointer_array_append_dword(this + 3, i);
    result = rf_solid_face_next_link(i);
  }
  return result;
}

