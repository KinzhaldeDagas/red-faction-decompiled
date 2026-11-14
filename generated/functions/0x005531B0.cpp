// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005531B0 rf_solid_subdivide_selected_faces_centroid
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Snapshots selected faces+216 into temporary array,then calls5559D0(solid,face,keepOriginal0,selectDerived1) for each. Thus every valid face with>=3 corners gets centroid vertex and n triangle faces,original removed;even triangles subdivide into3. Snapshot protects iteration against selection mutation. Frees temporary backing,no transaction/undo or returned counts in this body.
void __thiscall rf_solid_subdivide_selected_faces_centroid(char *this)
{
  int *v1; // eax
  int *v2; // eax
  void *v4[3]; // [esp+8h] [ebp-20h] BYREF
  int i; // [esp+14h] [ebp-14h]
  int first_dword; // [esp+18h] [ebp-10h]
  int v7; // [esp+24h] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(this + 216);
  rf_dword_array_construct_capacity(v4, first_dword);
  v7 = 0;
  for ( i = 0; i < first_dword; ++i )
  {
    v1 = (int *)sub_552200((_DWORD *)this + 54, i);
    rf_pointer_array_append_dword(v4, *v1);
  }
  for ( i = 0; i < first_dword; ++i )
  {
    v2 = (int *)sub_552200(v4, i);
    rf_solid_subdivide_face_centroid_fan(this, *v2, 0, 1);
  }
  v7 = -1;
  rf_pointer_array_destroy_backing_storage(v4);
}

