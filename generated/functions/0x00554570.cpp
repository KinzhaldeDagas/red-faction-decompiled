// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00554570 rf_solid_weld_selected_vertices_to_last
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Requires at least two selected vertices204. Copies selection to stable temporary storage, chooses LAST vertex as survivor, and merges each preceding vertex into it with 51ABC0(solid,survivor,removed). Computes/copies first two coordinates into unused local vector storage. Appends survivor to selection204 without uniqueness check. Does not average/move the survivor here.
void __thiscall rf_solid_weld_selected_vertices_to_last(int *this)
{
  float **v1; // eax
  float **v2; // eax
  int *v3; // eax
  int *v4; // eax
  float copy_result[3]; // [esp+8h] [ebp-48h] BYREF
  float destination[3]; // [esp+14h] [ebp-3Ch] BYREF
  int v8; // [esp+20h] [ebp-30h]
  void *v9[3]; // [esp+24h] [ebp-2Ch] BYREF
  float source[3]; // [esp+30h] [ebp-20h] BYREF
  int first_dword; // [esp+3Ch] [ebp-14h]
  int i; // [esp+40h] [ebp-10h]
  int v13; // [esp+4Ch] [ebp-4h]

  first_dword = rf_receiver_get_first_dword(this + 51);
  if ( first_dword >= 2 )
  {
    rf_dword_array_construct_capacity(v9, 0);
    v13 = 0;
    v1 = (float **)sub_552200(this + 51, 0);
    rf_vector3_copy_return_destination(destination, *v1);
    v2 = (float **)sub_552200(this + 51, 1);
    rf_vector3_copy_return_destination(source, *v2);
    rf_vector_copy(destination, copy_result, source);
    for ( i = 0; i < first_dword; ++i )
    {
      v3 = (int *)sub_552200(this + 51, i);
      rf_pointer_array_append_dword(v9, *v3);
    }
    v8 = *(_DWORD *)sub_552200(v9, first_dword - 1);
    for ( i = 0; i < first_dword - 1; ++i )
    {
      v4 = (int *)sub_552200(v9, i);
      rf_solid_merge_vertex_into_survivor(this, v8, *v4);
    }
    rf_pointer_array_append_dword(this + 51, v8);
    v13 = -1;
    rf_pointer_array_destroy_backing_storage(v9);
  }
}

