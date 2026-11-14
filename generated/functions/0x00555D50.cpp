// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00555D50 rf_solid_deselect_faces_matching_uv_controller_key
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Traverses faces112, and for matching DWORD Face56 key removes first matching selected-face pointer216 if present. Does not destroy geometry or change face metadata; repeated selection duplicates beyond first can remain.
void __thiscall rf_solid_deselect_faces_matching_uv_controller_key(void *this, int a2)
{
  int index; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = rf_receiver_get_first_dword((char *)this + 112); i; i = rf_solid_face_next_link(i) )
  {
    if ( *(_DWORD *)(i + 56) == a2 )
    {
      index = rf_pointer_array_find_index((_DWORD *)this + 54, i);
      if ( index > -1 )
        rf_pointer_array_erase_index_unchecked((_DWORD *)this + 54, index);
    }
  }
}

