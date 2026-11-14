// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419200 rf_clutter_spawn_authored_debris
// UNREALRED VERIFIED [clutter-debris-decode]: Iterates real debris V3D submeshes and creates one type-3 piece per submesh with decoded center, velocity, lifetime, material, and sound-set state.
_DWORD *__cdecl rf_clutter_spawn_authored_debris(int a1, char *a2, int a3, int a4, float a5, std::exception *a6)
{
  _DWORD *result; // eax
  float *v7; // eax
  const float *v8; // eax
  float *v9; // eax
  char *v10; // eax
  float scalar; // [esp+Ch] [ebp-D8h]
  float scalara; // [esp+Ch] [ebp-D8h]
  float v13; // [esp+10h] [ebp-D4h]
  float v14; // [esp+14h] [ebp-D0h]
  float v15[3]; // [esp+18h] [ebp-CCh] BYREF
  float scaled_result[3]; // [esp+24h] [ebp-C0h] BYREF
  _BYTE v17[12]; // [esp+30h] [ebp-B4h] BYREF
  float copy_result[3]; // [esp+3Ch] [ebp-A8h] BYREF
  float sum_result[3]; // [esp+48h] [ebp-9Ch] BYREF
  float v20; // [esp+54h] [ebp-90h] BYREF
  float v21; // [esp+58h] [ebp-8Ch]
  float v22; // [esp+5Ch] [ebp-88h]
  float rhs[3]; // [esp+60h] [ebp-84h] BYREF
  float destination[3]; // [esp+6Ch] [ebp-78h] BYREF
  float v25[9]; // [esp+78h] [ebp-6Ch] BYREF
  float v26[3]; // [esp+9Ch] [ebp-48h] BYREF
  float v27[6]; // [esp+A8h] [ebp-3Ch] BYREF
  int v28; // [esp+C0h] [ebp-24h]
  int v29; // [esp+C4h] [ebp-20h]
  int v30; // [esp+CCh] [ebp-18h]
  int auxiliary; // [esp+D4h] [ebp-10h] BYREF
  int i; // [esp+D8h] [ebp-Ch]
  int v33; // [esp+DCh] [ebp-8h]
  _DWORD *v34; // [esp+E0h] [ebp-4h]

  result = (_DWORD *)rf_model_handle_load_v3m_mode1(a2, 1, (void *)0xFFFFFFFF);
  v34 = result;
  if ( result )
  {
    v33 = rf_model_handle_node_count_adapter((int)v34);
    for ( i = 0; i < v33; ++i )
    {
      rf_vector3_default_construct_noop(rhs);
      rf_geomod_debris_spawn_config_init((int)destination);
      rf_vmesh_submesh_bounds_get(v34, i, (int)rhs, &v20);
      rf_vector_rotate_by_matrix3(rhs, (float *)(a1 + 72));
      v7 = rf_vector_add((const float *)(a1 + 60), sum_result, rhs);
      rf_vector_copy(destination, copy_result, v7);
      rf_matrix3_copy(v25, (const float *)(a1 + 72));
      v8 = (const float *)rf_vector3_normalized_copy_unchecked(rhs, (int)v17);
      v9 = rf_vector_multiply_scalar(v8, scaled_result, a5);
      rf_vector_copy(v26, v15, v9);
      v22 = rf_random_float_range(1.0, 4.0) * a5;
      rf_random_unit_vector(v27);
      rf_vector3_scale_in_place_return_self(v27, v22);
      scalar = (float)a4;
      v14 = (double)a4 / 10.0;
      scalara = rf_random_float_range(v14, scalar);
      LODWORD(v27[3]) = (int)rf_math_ceil_float(scalara);
      v27[4] = *(float *)(a1 + 508);
      LODWORD(v27[5]) = a3;
      v28 = -2147483640;
      if ( rf_material_debris_bitmap_get(*(_DWORD *)(a1 + 508), &auxiliary) != -1 )
        v28 |= 2u;
      if ( a3 >= 0 )
        v28 |= 1u;
      v29 = 0x10000;
      if ( a6 )
      {
        if ( rf_rf_string_not_equals_cstring_case_insensitive((int)a6, (char *)byte_631750) )
        {
          v10 = (char *)rf_string_object_c_str_or_empty(a6);
          v30 = rf_material_custom_sound_set_find(v10);
        }
      }
      v21 = (double)*(int *)(a1 + 508) * v20;
      v13 = v20 * 0.75;
      rf_physical_debris_piece_create(
        *(_DWORD *)(a1 + 44),
        a2,
        (void *)LODWORD(v21),
        destination,
        i,
        (void *)LODWORD(v13));
    }
    return (_DWORD *)rf_model_handle_destroy_cdecl_adapter(v34);
  }
  return result;
}

