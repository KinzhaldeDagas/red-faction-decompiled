// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005530D0 rf_solid_triangulate_selected_faces_fan
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, atlas ownership, lightmap seam lifecycle, selected-face topology, SDK misidentification, x87 return ABI and PE bytes): Thiscall solid. Snapshots current selected face pointers from member+216 into temporary DWORD array,then passes each to51D0D0 with solidECX,face,startCornerNULL,selectDerived1. Snapshot keeps iteration stable while derived triangles are selected and original faces removed. Triangles(count3) left unchanged by helper;polygons>3 replaced by n-2 anchored fan triangles. Frees snapshot backing;no own geometry validation,rollback or per-face result aggregation.
void __thiscall rf_solid_triangulate_selected_faces_fan(char *this)
{
  int *v1; // eax
  void **v2; // eax
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
    v2 = (void **)sub_552200(v4, i);
    rf_solid_triangulate_face_fan_from_corner(this, *v2, nullptr, 1u);
  }
  v7 = -1;
  rf_pointer_array_destroy_backing_storage(v4);
}

