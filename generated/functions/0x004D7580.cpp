// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004D7580 rf_physics_state_initialize_from_setup
// UNREALRED VERIFIED [combat-signed-rotation-20261112]: Physics-state setup consumes object136 state and source setup; final common initializer4D7A00 stores setup mass/flags/angular/forces and invokes4D9F50. Do not infer rotation masks80/4000/8000 from UEground state or assume collision fraction1 at every frame. AuthoredNPC options from4811C0 are2/4, notplayeroption1, as separately verified in ctor.
// UNREALRED VERIFIED [combat-original-facing-20261112]: Reached setup mass>0 (or unordered) skips missing-mass/inertia derivation; entity42CB80 setup was memset0, so a positive mass plus nonempty copied class sphere list must NOT invent an identity inverse tensor. In mass<=0 sphere branch, radius-cubed isFLOAT, cubed*double4.188790321350098 isFLOAT-stored before density call, each density mass and tensor update FLOAT-stored, and mass accumulates onto existing setup20 rather than an invented reset0. Empty-sphere fallback separately appends center0/radius132 and sets identity tensor.4D7A00/9F50 later recomputes radius from actual copied body24 samples.
int __cdecl rf_physics_state_initialize_from_setup(int a1, int a2)
{
  int first_dword; // eax
  int element_address_unchecked; // eax
  float *v4; // eax
  double v5; // st7
  double v6; // st7
  float v8; // [esp-14h] [ebp-A4h] BYREF
  int v9; // [esp-10h] [ebp-A0h]
  int v10; // [esp-Ch] [ebp-9Ch]
  int v11; // [esp-8h] [ebp-98h]
  int v12; // [esp-4h] [ebp-94h]
  int v13; // [esp+0h] [ebp-90h]
  double v14; // [esp+4h] [ebp-8Ch]
  double v15; // [esp+Ch] [ebp-84h]
  float copy_result[3]; // [esp+1Ch] [ebp-74h] BYREF
  float v17[6]; // [esp+28h] [ebp-68h] BYREF
  float destination[3]; // [esp+40h] [ebp-50h] BYREF
  float v19; // [esp+4Ch] [ebp-44h]
  float v20; // [esp+50h] [ebp-40h]
  float v21; // [esp+58h] [ebp-38h]
  float v22; // [esp+5Ch] [ebp-34h]
  float source[3]; // [esp+60h] [ebp-30h] BYREF
  float v24; // [esp+6Ch] [ebp-24h]
  float v25; // [esp+70h] [ebp-20h]
  float v26; // [esp+74h] [ebp-1Ch]
  float v27; // [esp+78h] [ebp-18h] BYREF
  float v28; // [esp+7Ch] [ebp-14h]
  float v29; // [esp+80h] [ebp-10h]
  int j; // [esp+84h] [ebp-Ch]
  int k; // [esp+88h] [ebp-8h]
  int i; // [esp+8Ch] [ebp-4h]

  if ( (*(_DWORD *)(a2 + 148) & 0x70) != 0 )
  {
    if ( *(float *)(a2 + 20) <= 0.0 )
    {
      if ( rf_receiver_get_first_dword((void *)(a2 + 136)) <= 0 )
      {
        if ( *(_DWORD *)(a2 + 8) )
        {
          rf_vector3_default_construct_noop(source);
          *(float *)&v13 = rf_material_density_get(*(_DWORD *)(a2 + 16));
          *(float *)(a2 + 20) = rf_solid_sample_mass_inverse_inertia_and_recenter(
                                  (float *)*(_DWORD *)(a2 + 8),
                                  source,
                                  (float *)(a2 + 24),
                                  *(float *)&v13);
          rf_vector_accumulate((float *)(a2 + 60), source);
          *(float *)(a2 + 132) = 0.0;
          v24 = *(float *)(*(_DWORD *)(a2 + 8) + 844) * 0.5;
          for ( i = 0; i < 4; ++i )
          {
            for ( j = 0; j < 4; ++j )
            {
              for ( k = 0; k < 4; ++k )
              {
                v22 = flt_63FA00[*(_BYTE *)(k + 16 * i + *(_DWORD *)(a2 + 8) + 780 + 4 * j) & 0xF];
                if ( v22 > 0.25 )
                {
                  source[0] = (double)i * *(float *)(*(_DWORD *)(a2 + 8) + 844) + *(float *)(*(_DWORD *)(a2 + 8) + 848);
                  source[1] = (double)j * *(float *)(*(_DWORD *)(a2 + 8) + 844) + *(float *)(*(_DWORD *)(a2 + 8) + 852);
                  source[2] = (double)k * *(float *)(*(_DWORD *)(a2 + 8) + 844) + *(float *)(*(_DWORD *)(a2 + 8) + 856);
                  rf_vector_prefix_construct_noop(destination);
                  rf_vector_copy(destination, copy_result, source);
                  v19 = v24 * v22;
                  v20 = -1.0;
                  rf_record24_copy_construct_six_floats(&v8, destination);
                  rf_array24_append_record_by_value((int *)(a2 + 136), v8, v9, v10, v11, v12, v13);
                  v5 = rf_vector_length_squared(source);
                  v21 = v5 + v19 * v19;
                  if ( *(float *)(a2 + 132) < (double)v21 )
                    *(float *)(a2 + 132) = v21;
                }
              }
            }
          }
          *(float *)(a2 + 132) = rf_sqrt_float(*(float *)(a2 + 132));
        }
        else
        {
          v6 = *(float *)(a2 + 132) * *(float *)(a2 + 132);
          v13 = *(int *)(a2 + 16);
          v14 = v6;
          *(float *)(a2 + 20) = rf_material_density_get(v13) * v6;
        }
      }
      else
      {
        for ( i = 0; ; ++i )
        {
          first_dword = rf_receiver_get_first_dword((void *)(a2 + 136));
          if ( i >= first_dword )
            break;
          element_address_unchecked = rf_array24_get_element_address_unchecked((_DWORD *)(a2 + 136), i);
          v25 = *(float *)(element_address_unchecked + 12)
              * *(float *)(element_address_unchecked + 12)
              * *(float *)(element_address_unchecked + 12);
          v13 = *(int *)(a2 + 16);
          v15 = v25 * 4.188790321350098;
          v26 = rf_material_density_get(v13) * v15;
          v4 = (float *)rf_array24_get_element_address_unchecked((_DWORD *)(a2 + 136), i);
          rf_vector3_copy_return_destination(&v27, v4);
          *(float *)(a2 + 24) = (v28 * v28 + v29 * v29) * v26 + *(float *)(a2 + 24);
          *(float *)(a2 + 28) = *(float *)(a2 + 28) - v26 * v27 * v28;
          *(float *)(a2 + 32) = *(float *)(a2 + 32) - v26 * v27 * v29;
          *(float *)(a2 + 36) = *(float *)(a2 + 36) - v26 * v28 * v27;
          *(float *)(a2 + 40) = (v27 * v27 + v29 * v29) * v26 + *(float *)(a2 + 40);
          *(float *)(a2 + 44) = *(float *)(a2 + 44) - v26 * v28 * v29;
          *(float *)(a2 + 48) = *(float *)(a2 + 48) - v26 * v29 * v27;
          *(float *)(a2 + 52) = *(float *)(a2 + 52) - v26 * v29 * v28;
          *(float *)(a2 + 56) = (v27 * v27 + v28 * v28) * v26 + *(float *)(a2 + 56);
          *(float *)(a2 + 20) = *(float *)(a2 + 20) + v26;
        }
        rf_matrix3_inverse_in_place_if_nonsingular((float *)(a2 + 24));
      }
    }
    if ( !rf_receiver_get_first_dword((void *)(a2 + 136)) )
    {
      rf_vector_prefix_construct_noop(v17);
      rf_vector3_zero_return_destination(v17);
      v17[3] = *(float *)(a2 + 132);
      v17[4] = -1.0;
      rf_record24_copy_construct_six_floats(&v8, v17);
      rf_array24_append_record_by_value((int *)(a2 + 136), v8, v9, v10, v11, v12, v13);
      rf_identity_orientation_matrix((float *)(a2 + 24));
    }
  }
  return rf_physics_state_copy_setup(a1, a2, 0);
}

