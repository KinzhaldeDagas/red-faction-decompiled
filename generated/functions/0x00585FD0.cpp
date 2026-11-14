// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00585FD0 rf_character_instance_evaluate_pose
// UNREALRED VERIFIED [animation-mix-decode]: Evaluates normalized per-bone state/action contributions and produces a parent-first composed pose.
float *__cdecl rf_character_instance_evaluate_pose(int a1, int a2, int a3)
{
  float *result; // eax
  float *v4; // eax
  float *v5; // eax
  int v6; // esi
  double v7; // st7
  float *v8; // eax
  const float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // [esp+Ch] [ebp-690h]
  float *v16; // [esp+Ch] [ebp-690h]
  float *v17; // [esp+10h] [ebp-68Ch]
  float *v18; // [esp+10h] [ebp-68Ch]
  float *v19; // [esp+14h] [ebp-688h]
  float *v20; // [esp+14h] [ebp-688h]
  float v21[3]; // [esp+1Ch] [ebp-680h] BYREF
  float v22[3]; // [esp+28h] [ebp-674h] BYREF
  float sum_result[3]; // [esp+34h] [ebp-668h] BYREF
  float v24[12]; // [esp+40h] [ebp-65Ch] BYREF
  float v25[3]; // [esp+70h] [ebp-62Ch] BYREF
  float v26[3]; // [esp+7Ch] [ebp-620h] BYREF
  float v27[3]; // [esp+88h] [ebp-614h] BYREF
  float v28[3]; // [esp+94h] [ebp-608h] BYREF
  float v29[12]; // [esp+A0h] [ebp-5FCh] BYREF
  float copy_result[3]; // [esp+D0h] [ebp-5CCh] BYREF
  _BYTE v31[12]; // [esp+DCh] [ebp-5C0h] BYREF
  _BYTE v32[16]; // [esp+E8h] [ebp-5B4h] BYREF
  float v33[3]; // [esp+F8h] [ebp-5A4h] BYREF
  float v34[3]; // [esp+104h] [ebp-598h] BYREF
  float v35[3]; // [esp+110h] [ebp-58Ch] BYREF
  float v36[3]; // [esp+11Ch] [ebp-580h] BYREF
  float v37[12]; // [esp+128h] [ebp-574h] BYREF
  float v38[12]; // [esp+158h] [ebp-544h] BYREF
  int v39[4]; // [esp+188h] [ebp-514h] BYREF
  float v40[3]; // [esp+198h] [ebp-504h] BYREF
  int v41[4]; // [esp+1A4h] [ebp-4F8h] BYREF
  int v42[4]; // [esp+1B4h] [ebp-4E8h] BYREF
  float rhs[3]; // [esp+1C4h] [ebp-4D8h] BYREF
  int v44; // [esp+1D0h] [ebp-4CCh]
  float v45; // [esp+1D4h] [ebp-4C8h]
  int v46; // [esp+1D8h] [ebp-4C4h]
  float v47[172]; // [esp+1DCh] [ebp-4C0h] BYREF
  int v48; // [esp+48Ch] [ebp-210h]
  float v49; // [esp+490h] [ebp-20Ch]
  float v50; // [esp+494h] [ebp-208h]
  int j; // [esp+498h] [ebp-204h]
  float v52[12]; // [esp+49Ch] [ebp-200h] BYREF
  int v53; // [esp+4CCh] [ebp-1D0h]
  int v54; // [esp+4D0h] [ebp-1CCh]
  _OWORD v55[16]; // [esp+4D4h] [ebp-1C8h] BYREF
  int i; // [esp+5D4h] [ebp-C8h]
  int v57; // [esp+5D8h] [ebp-C4h]
  float destination[48]; // [esp+5DCh] [ebp-C0h] BYREF

  v54 = *(_DWORD *)(a3 + 7504) + 76;
  v57 = *(_DWORD *)(*(_DWORD *)(a3 + 7504) + 72);
  rf_vector_construct_no_unwind((char *)destination, 0xCu, 16, rf_vector3_default_construct_noop);
  rf_vector_construct_no_unwind(
    (char *)v55,
    0x10u,
    16,
    (void *(__thiscall *)(void *))rf_float4_construct_zero_zero_zero_one);
  for ( i = 0; i < a1; ++i )
  {
    v53 = *(unsigned __int8 *)(i + a2);
    result = (float *)*(unsigned __int16 *)(a3 + 7416);
    if ( (float *)*(unsigned __int16 *)(a3 + 48 * v53 + 5012) != result )
    {
      rf_affine3x4_default_construct_noop(v52);
      if ( *(int *)(a3 + 4816) >= 1 )
      {
        v49 = 1.0;
        if ( *(int *)(a3 + 7424) > -1 && *(float *)(a3 + 12 * *(_DWORD *)(a3 + 7424) + 4828) != 0.0 )
        {
          v46 = *(_DWORD *)(a3 + 12 * *(_DWORD *)(a3 + 7424) + 4820);
          v49 = 10.0
              - rf_rfa_track_weight_at_time(
                  (void *)*(_DWORD *)(*(_DWORD *)(a3 + 7504) + 4 * v46 + 3932),
                  v53,
                  *(_DWORD *)(a3 + 12 * *(_DWORD *)(a3 + 7424) + 4824),
                  0);
          v49 = v49 * 0.1000000014901161;
        }
        v50 = 0.0;
        v48 = 0;
        for ( j = 0; j < *(_DWORD *)(a3 + 4816); ++j )
        {
          if ( *(float *)(a3 + 12 * j + 4828) != 0.0 )
          {
            v6 = 12 * j;
            if ( *(_BYTE *)(*(_DWORD *)(a3 + 7504) + *(_DWORD *)(a3 + 12 * j + 4820) + 4620) )
            {
              v7 = rf_rfa_track_weight_at_time(
                     (void *)*(_DWORD *)(*(_DWORD *)(a3 + 7504) + 4 * *(_DWORD *)(a3 + 12 * j + 4820) + 3932),
                     v53,
                     *(_DWORD *)(a3 + 12 * j + 4824),
                     1);
              v45 = v7 * *(float *)(a3 + v6 + 4828) * v49;
            }
            else
            {
              v45 = rf_rfa_track_weight_at_time(
                      (void *)*(_DWORD *)(*(_DWORD *)(a3 + 7504) + 4 * *(_DWORD *)(a3 + 12 * j + 4820) + 3932),
                      v53,
                      *(_DWORD *)(a3 + 12 * j + 4824),
                      0)
                  * *(float *)(a3 + v6 + 4828);
            }
            if ( v45 > 0.0 )
            {
              v50 = v50 + v45;
              v47[v48] = v45;
              v44 = *(_DWORD *)(a3 + 12 * j + 4820);
              v8 = (float *)rf_rfa_sample_rotation_track(
                              *(void **)(*(_DWORD *)(a3 + 7504) + 4 * v44 + 3932),
                              (int)v32,
                              v53,
                              *(_DWORD *)(a3 + 12 * j + 4824));
              rf_float4_copy_return_destination((float *)&v55[v48], v8);
              v9 = (const float *)rf_rfa_sample_translation_track(
                                    *(void **)(*(_DWORD *)(a3 + 7504) + 4 * v44 + 3932),
                                    (int)v31,
                                    v53,
                                    *(_DWORD *)(a3 + 12 * j + 4824));
              rf_vector_copy(&destination[3 * v48++], copy_result, v9);
            }
          }
        }
        if ( v48 <= 0 )
        {
          v20 = rf_vector3_set_components_return_destination(v28, 0.0, 0.0, 0.0);
          v18 = rf_vector3_set_components_return_destination(v27, 0.0, 0.0, 1.0);
          v16 = rf_vector3_set_components_return_destination(v26, 0.0, 1.0, 0.0);
          v10 = rf_vector3_set_components_return_destination(v25, 1.0, 0.0, 0.0);
          v11 = rf_affine3x4_set_rows_translation(v29, v10, v16, v18, v20);
          rf_fixed_block48_copy(v52, v11);
        }
        else
        {
          for ( j = 0; j < v48; ++j )
          {
            if ( v47[j] > 0.0 )
              v47[j] = v47[j] / v50;
          }
          rf_character_blend_local_transforms(v52, (float *)v55, destination, v48, v47);
        }
      }
      else
      {
        v19 = rf_vector3_set_components_return_destination(v36, 0.0, 0.0, 0.0);
        v17 = rf_vector3_set_components_return_destination(v35, 0.0, 0.0, 1.0);
        v15 = rf_vector3_set_components_return_destination(v34, 0.0, 1.0, 0.0);
        v4 = rf_vector3_set_components_return_destination(v33, 1.0, 0.0, 0.0);
        v5 = rf_affine3x4_set_rows_translation(v37, v4, v15, v17, v19);
        rf_fixed_block48_copy(v52, v5);
      }
      if ( *(int *)(v54 + 76 * v53 + 72) <= -1 )
      {
        rf_vector3_default_construct_noop(rhs);
        rf_affine48_copy_translation_return_self(v52, rhs);
        v13 = rf_vector_add((const float *)(a3 + 4800), sum_result, rhs);
        rf_affine3x4_set_translation_return_source(v52, v13);
        v14 = rf_vector3_set_components_return_destination(v22, 0.0, 0.0, 0.0);
        rf_vector_copy((float *)(a3 + 4800), v21, v14);
        rf_fixed_block48_copy((void *)(a3 + 48 * v53), v52);
      }
      else
      {
        v12 = rf_matrix43_compose_parent_local(v52, v24, (float *)(a3 + 48 * *(_DWORD *)(v54 + 76 * v53 + 72)));
        rf_fixed_block48_copy((void *)(a3 + 48 * v53), v12);
      }
      *(_WORD *)(a3 + 48 * v53 + 5012) = *(_WORD *)(a3 + 7416);
      result = (float *)*(unsigned __int8 *)(a3 + 48 * v53 + 5052);
      if ( *(_BYTE *)(a3 + 48 * v53 + 5052) )
      {
        rf_affine3x4_get_translation((float *)(a3 + 48 * v53), v40);
        rf_affine3x4_default_construct_noop(v38);
        rf_affine3x4_copy_rotation_zero_translation(v38, (float *)(a3 + 48 * v53 + 5016));
        rf_quaternion_from_matrix3x3((float *)v41, v38);
        rf_quaternion_from_matrix3x3((float *)v39, (float *)(a3 + 48 * v53));
        rf_float4_construct_zero_zero_zero_one((float *)v42);
        rf_quaternion_interpolate((float *)v42, (float *)v39, (float *)v41, *(float *)(a3 + 48 * v53 + 5056));
        rf_quaternion_to_affine3x4_zero_translation((float *)v42, (float *)(a3 + 48 * v53));
        result = rf_affine3x4_set_translation_return_source((float *)(a3 + 48 * v53), v40);
      }
    }
  }
  return result;
}

