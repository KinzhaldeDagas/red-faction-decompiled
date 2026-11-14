// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00562440 rf_model_handle_get_indexed_bounds_sphere
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Corrected false fastcall to thiscall(handle,index,outCenter,outRadius), RET12. Tag2 ignores index and uses embedded mesh at definition8+6592, referenced mesh LOD-table translation/radius. Tag1 index-1 computes aggregate mesh sphere5B9A40; indexed path reads144byte mesh record from instance76, gets LOD center/radius. Tag3 index-1 sets center0 and radius=max(length(defMesh.position148)+defMesh.radius160) over static definition mesh count76; if no meshes uses25. Ignores animated runtime pose/nonmesh records for whole-scene sphere. Indexed scene kind0 uses FLAT index for runtime152*index+4/definition292*index+160 (decoded local unused). Kind1 gets subelement center runtime effect144+36*sub+12 and radius
// descriptor36;kind2 point center12/radius52;kind3 dummy center12/radius0;kind4 center descriptor0 and radius28 or sqrt((width28^2+height32^2)/4) depending definition168. Unknown leaves outputs untouched; no general bounds checks.
void __thiscall rf_model_handle_get_indexed_bounds_sphere(void *this, int a2, float *destination, float *a4)
{
  float *lod_table_translation; // eax
  int v5; // edi
  float *v6; // eax
  float *v7; // eax
  float v8; // [esp+14h] [ebp-B0h]
  float v10[3]; // [esp+20h] [ebp-A4h] BYREF
  float v11[3]; // [esp+2Ch] [ebp-98h] BYREF
  float v12[3]; // [esp+38h] [ebp-8Ch] BYREF
  float v13[3]; // [esp+44h] [ebp-80h] BYREF
  float v14[3]; // [esp+50h] [ebp-74h] BYREF
  float v15[3]; // [esp+5Ch] [ebp-68h] BYREF
  float v16[3]; // [esp+68h] [ebp-5Ch] BYREF
  float v17[3]; // [esp+74h] [ebp-50h] BYREF
  float v18[3]; // [esp+80h] [ebp-44h] BYREF
  float copy_result[3]; // [esp+8Ch] [ebp-38h] BYREF
  float v20[3]; // [esp+98h] [ebp-2Ch] BYREF
  float v21; // [esp+A4h] [ebp-20h]
  float v22; // [esp+A8h] [ebp-1Ch]
  int v23; // [esp+ACh] [ebp-18h] BYREF
  int v24; // [esp+B0h] [ebp-14h] BYREF
  int v25; // [esp+B4h] [ebp-10h] BYREF
  float v26; // [esp+B8h] [ebp-Ch]
  int i; // [esp+BCh] [ebp-8h]
  float v28; // [esp+C0h] [ebp-4h]

  switch ( *(_DWORD *)this )
  {
    case 2:
      rf_model_container_get_reference_mesh_sphere((_DWORD *)(*((_DWORD *)this + 2) + 6592), destination, a4);
      break;
    case 1:
      if ( a2 == -1 )
      {
        rf_mesh_collection_aggregate_bounds_sphere(*((_DWORD **)this + 1), destination, a4);
      }
      else
      {
        lod_table_translation = rf_model_mesh144_get_lod_table_translation(
                                  (_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 76) + 144 * a2),
                                  v20);
        rf_vector_copy(destination, copy_result, lod_table_translation);
        *a4 = rf_mesh144_get_lod_table_radius((_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 76) + 144 * a2));
      }
      break;
    case 3:
      if ( a2 == -1 )
      {
        if ( *(int *)(*((_DWORD *)this + 2) + 76) <= 0 )
        {
          v7 = rf_vector3_set_components_return_destination(v16, 0.0, 0.0, 0.0);
          rf_vector_copy(destination, v15, v7);
          *a4 = 25.0;
        }
        else
        {
          v28 = 0.0;
          for ( i = 0; i < *(_DWORD *)(*((_DWORD *)this + 2) + 76); ++i )
          {
            v5 = *(_DWORD *)(*((_DWORD *)this + 2) + 72);
            v26 = rf_vector3_length((float *)(v5 + 292 * i + 148)) + *(float *)(v5 + 292 * i + 160);
            v28 = rf_float_maximum_two_values(v28, v26);
          }
          v6 = rf_vector3_set_components_return_destination(v18, 0.0, 0.0, 0.0);
          rf_vector_copy(destination, v17, v6);
          *a4 = v28;
        }
      }
      else
      {
        rf_scene_definition_decode_flat_object_index(*((_DWORD **)this + 2), a2, &v25, &v24, &v23);
        switch ( v25 )
        {
          case 0:
            rf_vector_copy(destination, v14, (const float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 20) + 152 * a2 + 4));
            *a4 = *(float *)(*(_DWORD *)(*((_DWORD *)this + 2) + 72) + 292 * a2 + 160);
            break;
          case 1:
            *a4 = *(float *)(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 2) + 88) + 220 * v24 + 208) + 36);
            rf_vector_copy(
              destination,
              v12,
              (const float *)(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 1) + 28) + 164 * v24 + 144) + 36 * v23 + 12));
            break;
          case 2:
            *a4 = *(float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 24) + 60 * v24 + 52);
            rf_vector_copy(destination, v13, (const float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 24) + 60 * v24 + 12));
            break;
          case 3:
            *a4 = 0.0;
            rf_vector_copy(destination, v11, (const float *)(*(_DWORD *)(*((_DWORD *)this + 1) + 32) + 40 * v24 + 12));
            break;
          case 4:
            if ( *(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 2) + 88) + 220 * v24 + 168) )
            {
              *a4 = *(float *)(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 2) + 88) + 220 * v24 + 208) + 28);
            }
            else
            {
              v21 = *(float *)(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 2) + 88) + 220 * v24 + 208) + 28);
              v22 = *(float *)(*(_DWORD *)(*(_DWORD *)(*((_DWORD *)this + 2) + 88) + 220 * v24 + 208) + 32);
              v8 = v21 * v21 / 4.0 + v22 * v22 / 4.0;
              *a4 = rf_sqrt_float(v8);
            }
            rf_vector_copy(
              destination,
              v10,
              *(const float **)(*(_DWORD *)(*((_DWORD *)this + 2) + 88) + 220 * v24 + 208));
            break;
          default:
            return;
        }
      }
      break;
  }
}

