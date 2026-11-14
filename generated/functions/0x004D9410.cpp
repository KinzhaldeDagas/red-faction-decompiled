// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D9410 sub_4D9410
// UNREALRED VERIFIED [combat-selected-drop-item-20261111]: In supported contact path clears common+1A8 bit400000 and supporthandle+8AC, then onresolved contact object setsbit400000 and stores resolvedcommonhandle at+8AC. This is support-object state used by selecteddrop admission, not a named authored NoDrop field. Full native contact/physics owner remains distinct from host movement-floor adaptation.
void __cdecl sub_4D9410(int a1)
{
  int first_dword; // eax
  const float *element_address_unchecked; // eax
  float *v3; // eax
  int v4; // eax
  int v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float *v10; // eax
  float v11[4]; // [esp-8h] [ebp-26Ch] BYREF
  float v12; // [esp+8h] [ebp-25Ch]
  float scalar; // [esp+Ch] [ebp-258h]
  double v14; // [esp+14h] [ebp-250h]
  float v15[3]; // [esp+1Ch] [ebp-248h] BYREF
  float v16[3]; // [esp+28h] [ebp-23Ch] BYREF
  float v17[3]; // [esp+34h] [ebp-230h] BYREF
  int v18[3]; // [esp+40h] [ebp-224h] BYREF
  float scaled_result[3]; // [esp+4Ch] [ebp-218h] BYREF
  float v20[3]; // [esp+58h] [ebp-20Ch] BYREF
  float v21[3]; // [esp+64h] [ebp-200h] BYREF
  float sum_result[3]; // [esp+70h] [ebp-1F4h] BYREF
  float copy_result[4]; // [esp+7Ch] [ebp-1E8h] BYREF
  float out_vector[3]; // [esp+8Ch] [ebp-1D8h] BYREF
  int v25; // [esp+98h] [ebp-1CCh]
  float v26; // [esp+9Ch] [ebp-1C8h]
  float v27; // [esp+A0h] [ebp-1C4h]
  float rhs[3]; // [esp+A4h] [ebp-1C0h] BYREF
  float destination; // [esp+B0h] [ebp-1B4h] BYREF
  float v30; // [esp+B4h] [ebp-1B0h]
  float v31[3]; // [esp+BCh] [ebp-1A8h] BYREF
  void *v32[23]; // [esp+C8h] [ebp-19Ch] BYREF
  float v33[6]; // [esp+124h] [ebp-140h] BYREF
  float v34[34]; // [esp+13Ch] [ebp-128h] BYREF
  void *v35[12]; // [esp+1C4h] [ebp-A0h] BYREF
  float v36[6]; // [esp+1F4h] [ebp-70h] BYREF
  float v37; // [esp+20Ch] [ebp-58h]
  int v38; // [esp+210h] [ebp-54h]
  int v39; // [esp+224h] [ebp-40h]
  float v40[6]; // [esp+23Ch] [ebp-28h] BYREF
  int i; // [esp+254h] [ebp-10h]
  int v42; // [esp+260h] [ebp-4h]

  rf_physics_state_construct_empty_sphere_collection((char *)v32);
  v42 = 0;
  rf_vector3_default_construct_noop(&destination);
  rf_vector3_default_construct_noop(v31);
  rf_vector3_default_construct_noop(rhs);
  if ( *(float *)(a1 + 268) >= 0.0 )
  {
    if ( *(float *)(a1 + 268) < 0.8500000238418579
      || *(_DWORD *)(a1 + 4992) == -1 && (*(_DWORD *)(a1 + 424) & 0x18000000) == 0 )
    {
      v42 = -1;
      rf_common_embedded_destroy_pointer_array(v32);
    }
    else
    {
      *(_DWORD *)(a1 + 424) &= ~0x400000u;
      *(_DWORD *)(a1 + 2220) = 0;
      v35[10] = *(void **)(a1 + 428);
      rf_matrix3_copy(v34, (const float *)(a1 + 252));
      rf_vector_prefix_construct_noop(v40);
      rf_vector3_zero_return_destination(v40);
      LODWORD(copy_result[3]) = v11;
      rf_record24_copy_construct_six_floats(v11, v40);
      rf_array24_append_record_by_value(
        (int *)v35,
        v11[0],
        SLODWORD(v11[1]),
        SLODWORD(v11[2]),
        SLODWORD(v11[3]),
        SLODWORD(v12),
        SLODWORD(scalar));
      for ( i = 0; ; ++i )
      {
        first_dword = rf_receiver_get_first_dword((void *)(a1 + 388));
        if ( i >= first_dword )
          break;
        if ( *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i) + 16) > 0.0 )
        {
          v27 = *(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i) + 12) * 0.5;
          element_address_unchecked = (const float *)rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i);
          rf_vector_copy(&destination, copy_result, element_address_unchecked);
          rf_vector_rotate_by_matrix3(&destination, (float *)(a1 + 252));
          rf_vector_accumulate(&destination, (float *)(a1 + 228));
          v30 = v30 - v27;
          scalar = 0.0;
          v12 = -*(float *)(rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i) + 20);
          rf_vector3_set_components_thiscall(rhs, 0.0, v12, scalar);
          v3 = rf_vector_add(&destination, sum_result, rhs);
          rf_vector_copy(v31, v21, v3);
          rf_vector_copy(v33, v20, &destination);
          v34[33] = v27;
          v4 = rf_array24_get_element_address_unchecked(v35, 0);
          *(float *)(v4 + 12) = v27;
          v37 = 1.0;
          if ( rf_physics_shape_sweep_movers_and_static_world(&destination, v31, (int)v32, v36) )
          {
            v14 = 1.0 - v37;
            v5 = rf_array24_get_element_address_unchecked((_DWORD *)(a1 + 388), i);
            v26 = *(float *)(v5 + 16) * v14 * *(float *)(a1 + 152);
            v6 = rf_vector_multiply_scalar(&flt_87BF48, scaled_result, v26);
            rf_vector_accumulate((float *)(a1 + 360), v6);
            LODWORD(scalar) = a1 + 228;
            v12 = COERCE_FLOAT(out_vector);
            v7 = rf_vector_scale((float *)v18, v37, rhs);
            v8 = rf_vector_add(&destination, v17, v7);
            rf_vector_subtract(v8, (float *)LODWORD(v12), (const float *)LODWORD(scalar));
            scalar = v26;
            v12 = COERCE_FLOAT(v15);
            v9 = rf_vector_cross(out_vector, v16, (float *)(a1 + 264));
            v10 = rf_vector_multiply_scalar(v9, (float *)LODWORD(v12), scalar);
            rf_vector_accumulate((float *)(a1 + 372), v10);
            rf_physics_hit_record68_copy_fields((float *)(a1 + 436), v36);
            v25 = rf_object_resolve_handle(v39);
            if ( v25 )
            {
              *(_DWORD *)(a1 + 424) |= 0x400000u;
              *(_DWORD *)(a1 + 2220) = *(_DWORD *)(v25 + 44);
            }
            *(_DWORD *)(a1 + 4992) = v38;
          }
        }
      }
      rf_pointer_array_release_storage(v35);
      v42 = -1;
      rf_common_embedded_destroy_pointer_array(v32);
    }
  }
  else
  {
    *(_DWORD *)(a1 + 4992) = -1;
    v42 = -1;
    rf_common_embedded_destroy_pointer_array(v32);
  }
}

