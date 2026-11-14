// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00555CF0 rf_solid_select_faces_matching_uv_controller_key
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Traverses all faces112 and appends uniquely into selected-face array216 when DWORD Face56 equals requested key. Does not clear other selected faces or set face flag bits; no bitmap comparison.
void __thiscall rf_solid_select_faces_matching_uv_controller_key(void *this, int a2)
{
  int i; // [esp+4h] [ebp-4h]

  for ( i = rf_receiver_get_first_dword((char *)this + 112); i; i = rf_solid_face_next_link(i) )
  {
    if ( *(_DWORD *)(i + 56) == a2 )
      rf_pointer_array_append_unique((_DWORD *)this + 54, i);
  }
}

