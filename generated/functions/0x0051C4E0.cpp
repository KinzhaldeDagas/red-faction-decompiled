// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0051C4E0 rf_solid_translate_by_subtracting_offset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall solid,one offset-vector pointer,RET4. Iterates stored vertex-pointer array120 and subtracts offset from EVERY entry in place;duplicates would be translated repeatedly. Re-finalizes geometry of every face in list112. Subtracts same offset from stored bounds min72/max84,and INCREASES scalar96 by length(offset),rather than recomputing radius or translating center100. No bounds recomputation,room/spatial-tree rebuild,UV projection,pointer/finite/alias validation or explicit stable return value;stored int EAX is residue. Positive supplied offset moves geometry in NEGATIVE direction. Used by primitive centering and51BF40.
int __thiscall rf_solid_translate_by_subtracting_offset(float *this, float *a2)
{
  float **v2; // eax
  int result; // eax
  int j; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(this + 30); ++i )
  {
    v2 = (float **)sub_552200((_DWORD *)this + 30, i);
    rf_vector_subtract_in_place(*v2, a2);
  }
  for ( j = rf_receiver_get_first_dword(this + 28); j; j = rf_solid_face_next_link(j) )
    rf_geomod_face_finalize_geometry(j, 0, 0);
  rf_vector_subtract_in_place(this + 18, a2);
  rf_vector_subtract_in_place(this + 21, a2);
  *(this + 24) = rf_vector3_length(a2) + *(this + 24);
  return result;
}

