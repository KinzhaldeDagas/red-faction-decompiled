// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00556220 rf_solid_replace_face_bitmap_handles
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): Traverses all faces112 and calls535780(face,oldHandle,newHandle), replacing bitmap48 only on exact DWORD equality. Does not regenerate UVs or validate handles, and affects all faces irrespective of selection.
void __thiscall rf_solid_replace_face_bitmap_handles(void *this, int a2, int a3)
{
  _DWORD *i; // [esp+4h] [ebp-4h]

  for ( i = (_DWORD *)rf_receiver_get_first_dword((char *)this + 112); i; i = (_DWORD *)rf_solid_face_next_link((int)i) )
    rf_face_replace_bitmap_handle_if_equal(i, a2, a3);
}

