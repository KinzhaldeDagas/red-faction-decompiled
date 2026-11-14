// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005170E0 sub_5170E0
// UNREALRED VERIFIED [combat-native-query-20261104]: Cached-owner crossing query seeds all ordinary-room roots (including sky) when room argumentnull; filters face flags4/8, uses two-sided56BDB0 and abs(fraction)<=1.000100016593933, finite projected containment and epsilon-expanded segment bounds. It is not the particle front-plane strict t<1 trace.517060 calls this null-room form before deciding to rerun point-room lookup.
char __cdecl sub_5170E0(int a1, int a2, float *rhs, float *lhs)
{
  float *v4; // eax
  int first_dword; // eax
  int v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v10; // [esp+4h] [ebp-10A8h]
  float v11[3]; // [esp+8h] [ebp-10A4h] BYREF
  float sum_result[3]; // [esp+14h] [ebp-1098h] BYREF
  float scaled_result[3]; // [esp+20h] [ebp-108Ch] BYREF
  float v14[3]; // [esp+2Ch] [ebp-1080h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-1074h] BYREF
  float out_vector[3]; // [esp+44h] [ebp-1068h] BYREF
  float scalar; // [esp+50h] [ebp-105Ch] BYREF
  float v18; // [esp+54h] [ebp-1058h]
  char v19; // [esp+5Bh] [ebp-1051h]
  float *v20; // [esp+5Ch] [ebp-1050h]
  float *j; // [esp+60h] [ebp-104Ch]
  int i; // [esp+64h] [ebp-1048h]
  float v23[3]; // [esp+68h] [ebp-1044h] BYREF
  float destination[3]; // [esp+74h] [ebp-1038h] BYREF
  int v25; // [esp+80h] [ebp-102Ch]
  _DWORD v26[1025]; // [esp+84h] [ebp-1028h]
  float v27[3]; // [esp+1088h] [ebp-24h] BYREF
  float v28[3]; // [esp+1094h] [ebp-18h] BYREF
  float v29[3]; // [esp+10A0h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v27);
  v25 = 0;
  rf_force_sample44_construct_vectors_noop((char *)v23);
  v4 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(destination, copy_result, v4);
  rf_vector_copy(v23, v14, rhs);
  rf_vector3_default_construct_noop(v28);
  rf_vector3_default_construct_noop(v29);
  rf_segment_bounds_build(v28, v29, rhs, lhs);
  rf_vector3_subtract_scalar_in_place(v28, 0.000099999997);
  rf_vector3_add_scalar_in_place(v29, 0.000099999997);
  if ( a2 )
  {
    v26[v25++] = *(_DWORD *)(a2 + 60);
  }
  else
  {
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword((void *)(a1 + 156));
      if ( i >= first_dword )
        break;
      v6 = sub_552200((_DWORD *)(a1 + 156), i);
      if ( *(_DWORD *)(*(_DWORD *)v6 + 60) )
        v26[v25++] = *(_DWORD *)(*(_DWORD *)v6 + 60);
    }
  }
  while ( v25 > 0 )
  {
    v20 = (float *)v26[--v25];
    if ( rf_aabb_overlap_strict_ordered(v20, v20 + 3, v28, v29)
      && rf_segment_intersects_aabb(v20, v20 + 3, rhs, lhs, v27) )
    {
      for ( j = (float *)rf_receiver_get_first_dword(v20 + 6); j; j = (float *)rf_face_next_spatial_node_link((int)j) )
      {
        if ( rf_geomod_face_flags_eligible((_DWORD *)j + 10) && rf_aabb_overlap_strict_ordered(j + 4, j + 7, v28, v29) )
        {
          v19 = sub_56BDB0((int)v23, j, &scalar);
          v10 = fabs(scalar);
          v18 = v10;
          if ( v19 )
          {
            if ( v18 <= 1.000100016593933 )
            {
              v7 = rf_vector_multiply_scalar(destination, scaled_result, scalar);
              v8 = rf_vector_add(v23, sum_result, v7);
              rf_vector_copy(v27, v11, v8);
              if ( rf_geomod_face_contains_projected_point(j, (int)v27) )
                return 1;
            }
          }
        }
      }
      if ( *((_DWORD *)v20 + 8) )
        v26[v25++] = *((_DWORD *)v20 + 8);
      if ( *((_DWORD *)v20 + 9) )
        v26[v25++] = *((_DWORD *)v20 + 9);
    }
  }
  return 0;
}

