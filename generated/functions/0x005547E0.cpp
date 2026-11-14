// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005547E0 rf_solid_weld_selected_vertex_components_to_centroids
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, vertex selection, directed edge incidence, weld topology, corner UV copying and receiver ABI): Labels selected-vertex edge-connected components from label0. Allocates one24-byte temporary record per component: XYZ sum plus member array12, then averages original selected coordinates. For each component uses FIRST member as survivor, merges remaining members with 51ABC0, copies arithmetic centroid into survivor, repairs its incident faces with 553B10(solid,vertex), and destroys the temporary record. No allocation-null/member-count guards; member grouping uses vertex+28 scratch labels.
void __thiscall rf_solid_weld_selected_vertex_components_to_centroids(char *this)
{
  int v1; // eax
  float **v2; // eax
  int v3; // eax
  float **v4; // eax
  int v5; // eax
  float v6; // [esp+Ch] [ebp-6Ch]
  float *v7; // [esp+10h] [ebp-68h]
  float copy_result[3]; // [esp+20h] [ebp-58h] BYREF
  void *v10; // [esp+2Ch] [ebp-4Ch]
  float *v11; // [esp+30h] [ebp-48h]
  int v12; // [esp+34h] [ebp-44h]
  int j; // [esp+38h] [ebp-40h]
  float *destination; // [esp+3Ch] [ebp-3Ch]
  float *source; // [esp+40h] [ebp-38h]
  int v16; // [esp+44h] [ebp-34h]
  float *v17; // [esp+48h] [ebp-30h]
  float *v18; // [esp+4Ch] [ebp-2Ch]
  int v19; // [esp+50h] [ebp-28h] BYREF
  void *v20[3]; // [esp+54h] [ebp-24h] BYREF
  int first_dword; // [esp+60h] [ebp-18h]
  int i; // [esp+64h] [ebp-14h]
  int v23; // [esp+68h] [ebp-10h]
  int v24; // [esp+74h] [ebp-4h]

  rf_dword_array_construct_capacity(v20, 0);
  v24 = 0;
  v19 = 0;
  rf_solid_label_selected_vertex_components(this, &v19);
  for ( i = 0; i < v19; ++i )
  {
    v10 = operator new(0x18u);
    LOBYTE(v24) = 1;
    if ( v10 )
      v7 = (float *)rf_vertex_component_record_construct((int)v10);
    else
      v7 = nullptr;
    v11 = v7;
    LOBYTE(v24) = 0;
    v18 = v7;
    rf_vector3_zero_return_destination(v7);
    rf_pointer_array_append_dword(v20, (int)v7);
  }
  first_dword = rf_receiver_get_first_dword(this + 204);
  for ( i = 0; i < first_dword; ++i )
  {
    v17 = *(float **)sub_552200((_DWORD *)this + 51, i);
    v23 = *((_DWORD *)v17 + 7);
    v1 = sub_552200(v20, v23);
    rf_pointer_array_append_dword((_DWORD *)(*(_DWORD *)v1 + 12), (int)v17);
    v2 = (float **)sub_552200(v20, v23);
    rf_vector_accumulate(*v2, v17);
  }
  for ( i = 0; i < v19; ++i )
  {
    v3 = sub_552200(v20, i);
    v16 = rf_receiver_get_first_dword((void *)(*(_DWORD *)v3 + 12));
    v6 = 1.0 / (double)v16;
    v4 = (float **)sub_552200(v20, i);
    rf_vector3_scale_in_place_return_self(*v4, v6);
  }
  for ( i = 0; i < v19; ++i )
  {
    source = *(float **)sub_552200(v20, i);
    destination = *(float **)sub_552200((_DWORD *)source + 3, 0);
    for ( j = 1; ; ++j )
    {
      v5 = rf_receiver_get_first_dword(source + 3);
      if ( j >= v5 )
        break;
      v12 = *(_DWORD *)sub_552200((_DWORD *)source + 3, j);
      rf_solid_merge_vertex_into_survivor((int *)this, (int)destination, v12);
    }
    rf_vector_copy(destination, copy_result, source);
    rf_solid_repair_faces_incident_to_vertex(this, destination);
    if ( source )
      rf_vertex_component_record_scalar_deleting_destructor(source, 1);
  }
  v24 = -1;
  rf_pointer_array_destroy_backing_storage(v20);
}

