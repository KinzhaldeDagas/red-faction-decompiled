// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042AF70 rf_entity_test_directional_death_clearance
// UNREALRED VERIFIED [death-selector-decode]: Tests two horizontal obstruction probes, two required floor probes, then nearby clutter in a 45-degree cone.
char __cdecl rf_entity_test_directional_death_clearance(int a1, char a2)
{
  double v2; // st7
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  double v9; // st7
  float v10; // [esp+Ch] [ebp-C4h]
  float v11; // [esp+10h] [ebp-C0h]
  float v12; // [esp+14h] [ebp-BCh]
  float v13[3]; // [esp+18h] [ebp-B8h] BYREF
  float v14[3]; // [esp+24h] [ebp-ACh] BYREF
  float v15[3]; // [esp+30h] [ebp-A0h] BYREF
  float v16[3]; // [esp+3Ch] [ebp-94h] BYREF
  float v17[3]; // [esp+48h] [ebp-88h] BYREF
  float scaled_result[3]; // [esp+54h] [ebp-7Ch] BYREF
  float copy_result[3]; // [esp+60h] [ebp-70h] BYREF
  float sum_result[3]; // [esp+6Ch] [ebp-64h] BYREF
  float v21; // [esp+78h] [ebp-58h]
  float v22[2]; // [esp+7Ch] [ebp-54h] BYREF
  float v23; // [esp+84h] [ebp-4Ch]
  int i; // [esp+88h] [ebp-48h]
  float lhs; // [esp+8Ch] [ebp-44h] BYREF
  float v26; // [esp+90h] [ebp-40h]
  float destination[3]; // [esp+98h] [ebp-38h] BYREF
  float scalar; // [esp+A4h] [ebp-2Ch]
  float v29; // [esp+A8h] [ebp-28h] BYREF
  float v30; // [esp+ACh] [ebp-24h]
  float rhs[3]; // [esp+B4h] [ebp-1Ch] BYREF
  float source[3]; // [esp+C0h] [ebp-10h] BYREF
  float v33; // [esp+CCh] [ebp-4h]

  if ( a2 == 1 )
    v2 = *(float *)(a1 + 384) * 3.0;
  else
    v2 = *(float *)(a1 + 384) * -3.0;
  scalar = v2;
  rf_vector_multiply_scalar((const float *)(a1 + 96), rhs, scalar);
  rf_vector_add((const float *)(a1 + 60), destination, rhs);
  if ( rf_geometry_segment_is_obstructed(a1 + 60, (int)destination, 1, 0) == 1 )
    return 0;
  rf_vector3_copy_return_destination(&lhs, (float *)(a1 + 60));
  v26 = v26 - *(float *)(a1 + 120) * 0.5;
  v4 = rf_vector_add(&lhs, sum_result, rhs);
  rf_vector_copy(destination, copy_result, v4);
  if ( rf_geometry_segment_is_obstructed((int)&lhs, (int)destination, 1, 0) == 1 )
    return 0;
  v33 = 1.0;
  v5 = rf_vector_multiply_scalar((const float *)(a1 + 96), scaled_result, scalar);
  v6 = rf_vector_multiply_scalar(v5, v17, 0.5);
  rf_vector_add((const float *)(a1 + 60), source, v6);
  rf_vector3_copy_return_destination(&v29, source);
  v30 = v30 - (*(float *)(a1 + 120) + v33);
  if ( !rf_geometry_segment_is_obstructed((int)source, (int)&v29, 1, 0) )
    return 0;
  v7 = rf_vector_multiply_scalar((const float *)(a1 + 96), v16, scalar);
  v8 = rf_vector_add((const float *)(a1 + 60), v15, v7);
  rf_vector_copy(source, v14, v8);
  rf_vector_copy(&v29, v13, source);
  v30 = v30 - (*(float *)(a1 + 120) + v33);
  if ( !rf_geometry_segment_is_obstructed((int)source, (int)&v29, 1, 0) )
    return 0;
  for ( i = rf_clutter_list_head; (_UNKNOWN *)i != &unk_666D18; i = *(_DWORD *)(i + 652) )
  {
    if ( (*(_DWORD *)(*(_DWORD *)(i + 660) + 116) & 4) != 0 )
    {
      v12 = fabs(scalar);
      v21 = v12 + *(float *)(i + 384);
      v21 = v21 * v21;
      v9 = rf_vector_distance_squared((const float *)(a1 + 60), (const float *)(i + 60));
      if ( v21 >= v9 )
      {
        rf_vector3_copy_return_destination(v22, (float *)(i + 60));
        rf_vector_inverse_translate_rotate_in_place(v22, a1 + 60, a1 + 72);
        if ( (a2 != 1 || v23 >= 0.0) && (a2 || v23 <= 0.0) )
        {
          v11 = fabs(v23);
          v10 = fabs(v22[0]);
          if ( v10 < (double)v11 )
            return 0;
        }
      }
    }
  }
  return 1;
}

