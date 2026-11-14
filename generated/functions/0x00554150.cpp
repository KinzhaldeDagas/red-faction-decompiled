// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00554150 rf_solid_extrude_selected_faces_with_edge_inset
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): ECX solid, stack(normalDistance,edgeInset,reverseNormal byte), RET12. For each live selected face, makes new cap corner position=old+edgeInset*(unit(next-old)+unit(previous-old)) +/- normalDistance*faceNormal. This is summed unit edges, not exact geometric miter distance; zero-edge normalize uses unitX fallback. Duplicates positions into solid vertices, copies four original UVs, finalizes cap and generated-UV-projects. Builds quad(oldCurrent,oldNext,newNext,newCurrent) per edge with all UV0, finalizes/projects. Removes original with final argument1. Iterates live selection by increasing index, so removal-induced compaction affects subsequent traversal. Ends by releasing selected-face array216 entirely. No
// new-face selection, room attachment, finalize-status check, or rollback.
void __thiscall rf_solid_extrude_selected_faces_with_edge_inset(void *this, float a2, float scalar, unsigned __int8 a4)
{
  int first_dword; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  int v10; // [esp+10h] [ebp-BCh]
  int v11; // [esp+14h] [ebp-B8h]
  int v12; // [esp+18h] [ebp-B4h]
  float v14[3]; // [esp+20h] [ebp-ACh] BYREF
  float sum_result[3]; // [esp+2Ch] [ebp-A0h] BYREF
  float v16[3]; // [esp+38h] [ebp-94h] BYREF
  float v17[3]; // [esp+44h] [ebp-88h] BYREF
  float v18[3]; // [esp+50h] [ebp-7Ch] BYREF
  float v19[3]; // [esp+5Ch] [ebp-70h] BYREF
  float copy_result[3]; // [esp+68h] [ebp-64h] BYREF
  float scaled_result[3]; // [esp+74h] [ebp-58h] BYREF
  float *v22; // [esp+80h] [ebp-4Ch]
  float v23[3]; // [esp+84h] [ebp-48h] BYREF
  float destination[3]; // [esp+90h] [ebp-3Ch] BYREF
  float rhs[3]; // [esp+9Ch] [ebp-30h] BYREF
  float out_vector[3]; // [esp+A8h] [ebp-24h] BYREF
  float *v27; // [esp+B4h] [ebp-18h]
  float *link; // [esp+B8h] [ebp-14h]
  float *vector; // [esp+BCh] [ebp-10h]
  int j; // [esp+C0h] [ebp-Ch]
  int v31; // [esp+C4h] [ebp-8h]
  int i; // [esp+C8h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    first_dword = rf_receiver_get_first_dword((char *)this + 216);
    if ( i >= first_dword )
      break;
    vector = *(float **)sub_552200((_DWORD *)this + 54, i);
    link = (float *)rf_solid_face_allocate_link(this, (const unsigned int *)vector + 10);
    for ( j = *((_DWORD *)vector + 16); j; j = v12 )
    {
      rf_vector_subtract(**(const float ***)(j + 20), out_vector, *(const float **)j);
      rf_vector_subtract(**(const float ***)(j + 24), destination, *(const float **)j);
      rf_vector_normalize(out_vector);
      rf_vector_normalize(destination);
      v5 = rf_vector_multiply_scalar(out_vector, scaled_result, scalar);
      rf_vector_copy(out_vector, copy_result, v5);
      v6 = rf_vector_multiply_scalar(destination, v19, scalar);
      rf_vector_copy(destination, v18, v6);
      rf_vector_multiply_scalar(vector, rhs, a2);
      if ( a4 )
      {
        v7 = rf_vector_scale(v17, -1.0, rhs);
        rf_vector_copy(rhs, v16, v7);
      }
      v8 = rf_vector_add(*(const float **)j, sum_result, out_vector);
      v9 = rf_vector_add(v8, v14, destination);
      rf_vector_add(v9, v23, rhs);
      v27 = rf_solid_vertex_copy_append(this, v23);
      rf_geomod_face_corner_append(
        link,
        (int)v27,
        *(float *)(j + 4),
        *(float *)(j + 8),
        *(float *)(j + 12),
        *(float *)(j + 16));
      if ( *(_DWORD *)(j + 20) == *((_DWORD *)vector + 16) )
        v12 = 0;
      else
        v12 = *(_DWORD *)(j + 20);
    }
    rf_geomod_face_finalize_geometry((int)link, nullptr, 0);
    rf_geomod_generated_uv_project((int)link);
    v31 = *((_DWORD *)link + 16);
    for ( j = *((_DWORD *)vector + 16); j; j = v11 )
    {
      v22 = (float *)rf_solid_face_allocate_link(this, (const unsigned int *)vector + 10);
      rf_geomod_face_corner_append(v22, *(_DWORD *)j, 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_corner_append(v22, **(_DWORD **)(j + 20), 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_corner_append(v22, **(_DWORD **)(v31 + 20), 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_corner_append(v22, *(_DWORD *)v31, 0.0, 0.0, 0.0, 0.0);
      rf_geomod_face_finalize_geometry((int)v22, nullptr, 0);
      rf_geomod_generated_uv_project((int)v22);
      if ( *(_DWORD *)(v31 + 20) == *((_DWORD *)link + 16) )
        v10 = 0;
      else
        v10 = *(_DWORD *)(v31 + 20);
      v31 = v10;
      if ( *(_DWORD *)(j + 20) == *((_DWORD *)vector + 16) )
        v11 = 0;
      else
        v11 = *(_DWORD *)(j + 20);
    }
    rf_solid_face_remove_destroy((int *)this, vector, 1);
  }
  rf_pointer_array_release_storage((void **)this + 54);
}

