// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005560B0 rf_solid_select_all_faces
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Clears selected-face array216 COUNT while retaining storage, traverses face list112 and appends every face without uniqueness checks. No vertex selection or face flag mutation. Return becomes null on exhausted list.
void __thiscall rf_solid_select_all_faces(void *this)
{
  int i; // [esp+4h] [ebp-4h]

  rf_pointer_array_clear_count_keep_storage((_DWORD *)this + 54);
  for ( i = rf_receiver_get_first_dword((char *)this + 112); i; i = rf_solid_face_next_link(i) )
    rf_pointer_array_append_dword((_DWORD *)this + 54, i);
}

