// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043D4D0 rf_blood_surface_mark_spawn_at_prop
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Require global option0x662E2C nonzero and owner context/model lookup results non-null. Use free mark; if none, select active mark with greatest age float+0 and move it to free ring BEFORE subsequent prop/raycast validation. Find named model prop, compose world transform, cast downward(0,-1,0); on hit position mark at hit+normal*0.01, orient to surface, derive color via0x539450 and retain region context+0x44. Initialize age/current size0,growth duration=argument3,max size=argument4,growth rate~pi/2/duration; move node free=>active. No duration-zero clamp. Failed prop/raycast after eviction does not reinstate previous mark.
void __cdecl rf_blood_surface_mark_spawn_at_prop(int a1, char *String1, float a3, float a4)
{
  float *v4; // eax
  float *v5; // eax
  _DWORD *v6; // eax
  int v7; // [esp+Ch] [ebp-148h]
  int v8; // [esp+10h] [ebp-144h] BYREF
  float v9[3]; // [esp+14h] [ebp-140h] BYREF
  float sum_result[3]; // [esp+20h] [ebp-134h] BYREF
  float scaled_result[3]; // [esp+2Ch] [ebp-128h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-11Ch] BYREF
  float v13[6]; // [esp+44h] [ebp-110h] BYREF
  float vector[3]; // [esp+5Ch] [ebp-F8h] BYREF
  float v15; // [esp+68h] [ebp-ECh]
  int i; // [esp+6Ch] [ebp-E8h]
  int v17; // [esp+70h] [ebp-E4h]
  char v18[52]; // [esp+74h] [ebp-E0h] BYREF
  float destination[3]; // [esp+A8h] [ebp-ACh] BYREF
  float v20[13]; // [esp+B4h] [ebp-A0h] BYREF
  int v21; // [esp+E8h] [ebp-6Ch]
  char v22[36]; // [esp+ECh] [ebp-68h] BYREF
  _DWORD v23[2]; // [esp+110h] [ebp-44h] BYREF
  float lhs[3]; // [esp+118h] [ebp-3Ch] BYREF
  _BYTE v25[16]; // [esp+124h] [ebp-30h] BYREF
  int v26; // [esp+134h] [ebp-20h]
  float source[3]; // [esp+138h] [ebp-1Ch] BYREF
  int named_node_index; // [esp+144h] [ebp-10h]
  char *definition_pointer; // [esp+148h] [ebp-Ch]
  int first_dword; // [esp+14Ch] [ebp-8h]
  int v31; // [esp+150h] [ebp-4h]

  if ( !dword_662E2C )
    return;
  first_dword = rf_receiver_get_first_dword((void *)a1);
  v31 = *(_DWORD *)(a1 + 128);
  definition_pointer = (char *)rf_model_handle_get_definition_pointer(v31);
  if ( !first_dword || !definition_pointer )
    return;
  v21 = unk_6E6228;
  if ( !unk_6E6228 )
  {
    v17 = 0;
    v15 = -1.0;
    for ( i = unk_6E6254; i; i = v7 )
    {
      if ( v15 < (double)*(float *)i )
      {
        v17 = i;
        v15 = *(float *)i;
      }
      if ( *(_DWORD *)(i + 76) == unk_6E6254 )
        v7 = 0;
      else
        v7 = *(_DWORD *)(i + 76);
    }
    v21 = v17;
    if ( unk_6E6254 == v17 )
    {
      if ( *(_DWORD *)(v21 + 76) == v21 )
      {
        *(_DWORD *)(v21 + 76) = 0;
        *(_DWORD *)(v21 + 80) = 0;
        unk_6E6254 = 0;
        goto LABEL_19;
      }
      unk_6E6254 = *(_DWORD *)(v21 + 76);
    }
    *(_DWORD *)(*(_DWORD *)(v21 + 80) + 76) = *(_DWORD *)(v21 + 76);
    *(_DWORD *)(*(_DWORD *)(v21 + 76) + 80) = *(_DWORD *)(v21 + 80);
    *(_DWORD *)(v21 + 76) = 0;
    *(_DWORD *)(v21 + 80) = 0;
LABEL_19:
    if ( unk_6E6228 )
    {
      *(_DWORD *)(v21 + 80) = *(_DWORD *)(unk_6E6228 + 80);
      *(_DWORD *)(v21 + 76) = unk_6E6228;
      *(_DWORD *)(*(_DWORD *)(unk_6E6228 + 80) + 76) = v21;
      *(_DWORD *)(unk_6E6228 + 80) = v21;
    }
    else
    {
      *(_DWORD *)(v21 + 76) = v21;
      *(_DWORD *)(v21 + 80) = v21;
      unk_6E6228 = v21;
    }
  }
  rf_vector3_default_construct_noop(source);
  rf_matrix3_construct(v22);
  named_node_index = rf_character_find_named_node_index(definition_pointer, String1);
  if ( named_node_index != -1
    || (named_node_index = rf_character_find_primary_bone_substring(definition_pointer, String1), named_node_index != -1) )
  {
    rf_vmesh_compose_prop_world_transform(v31, named_node_index, (float *)(a1 + 72), a1 + 60, (int)v22, source);
    rf_solid_collision_query_construct_clear_face_hint(v18);
    rf_solid_collision_result_construct_noop((int)v23);
    rf_vector_copy(destination, copy_result, source);
    rf_vector3_set_components_thiscall(v20, 0.0, -1.0, 0.0);
    v20[3] = 0.0;
    LODWORD(v20[4]) = 4;
    *(float *)&v23[1] = 3.4028235e38;
    rf_solid_sweep_query_in_selected_room((char *)rf_world_solid, (int)v18, v23, first_dword);
    if ( v23[0] > 0 )
    {
      rf_matrix3_construct((char *)v13);
      rf_orientation_matrix_from_direction(v13, (int)v25);
      v4 = rf_vector_multiply_scalar(vector, scaled_result, 0.0099999998);
      v5 = rf_vector_add(lhs, sum_result, v4);
      rf_vector_copy((float *)(v21 + 20), v9, v5);
      v6 = rf_world_face_sample_lightmap_rgb555((_DWORD *)rf_world_solid, &v8, v26, (int)lhs);
      *(_DWORD *)(v21 + 72) = *v6;
      rf_matrix3_copy((float *)(v21 + 32), v13);
      *(_DWORD *)(v21 + 68) = first_dword;
      *(float *)v21 = 0.0;
      *(float *)(v21 + 12) = a4;
      *(float *)(v21 + 8) = a3;
      *(float *)(v21 + 4) = 0.0;
      *(float *)(v21 + 16) = 1.570796370506287 / a3;
      if ( unk_6E6228 == v21 )
      {
        if ( *(_DWORD *)(v21 + 76) == v21 )
        {
          *(_DWORD *)(v21 + 76) = 0;
          *(_DWORD *)(v21 + 80) = 0;
          unk_6E6228 = 0;
          goto LABEL_30;
        }
        unk_6E6228 = *(_DWORD *)(v21 + 76);
      }
      *(_DWORD *)(*(_DWORD *)(v21 + 80) + 76) = *(_DWORD *)(v21 + 76);
      *(_DWORD *)(*(_DWORD *)(v21 + 76) + 80) = *(_DWORD *)(v21 + 80);
      *(_DWORD *)(v21 + 76) = 0;
      *(_DWORD *)(v21 + 80) = 0;
LABEL_30:
      if ( unk_6E6254 )
      {
        *(_DWORD *)(v21 + 80) = *(_DWORD *)(unk_6E6254 + 80);
        *(_DWORD *)(v21 + 76) = unk_6E6254;
        *(_DWORD *)(*(_DWORD *)(unk_6E6254 + 80) + 76) = v21;
        *(_DWORD *)(unk_6E6254 + 80) = v21;
      }
      else
      {
        *(_DWORD *)(v21 + 76) = v21;
        *(_DWORD *)(v21 + 80) = v21;
        unk_6E6254 = v21;
      }
    }
  }
}

