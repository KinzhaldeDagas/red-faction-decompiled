// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00535BF0 rf_geomod_face_ray_query_accumulate
// UNREALRED VERIFIED [trigger-airlock-20261022] Room lookup calls with owner=null. Coplanar plane classification is admitted as front in that case. Nearest distance ties prefer front over back. Positive hits nearer than boundary threshold request a retry before recording the candidate; last-attempt caller continues without storing that boundary candidate. Finite segment bounds are pruned before polygon intersection.
// UNREALRED VERIFIED [geomod-classification-20261028] Source-face query +0x24 is retained by 0x535B40. If start lies in target plane epsilon band, count actual source corners: Front iff front_count > back_count; ties choose Back. All-coplanar source corners set query +0x31, orientation from SOURCE face normal dot target normal <0 (ECX=[query+0x24] at 0x535DB1), not a centroid-front default. Decide nearest replacement at 0x535DF3..0x535E85 BEFORE finite containment 0x535EC9 and positive boundary-hit retry 0x535EEC. Within epsilon prefer Front over Back; same orientation replaces iff strictly closer. Losing candidates never request retry. Native epsilon is double(float(0.0001)), equivalent to 0.009999999747378752 cm in host units.
char __thiscall rf_geomod_face_ray_query_accumulate(int this, float *a2)
{
  float *v3; // eax
  float *v4; // eax
  int v5; // [esp+4h] [ebp-84h]
  int v6; // [esp+8h] [ebp-80h]
  int v7; // [esp+Ch] [ebp-7Ch]
  float v8; // [esp+10h] [ebp-78h]
  float v10[3]; // [esp+18h] [ebp-70h] BYREF
  float copy_result[3]; // [esp+24h] [ebp-64h] BYREF
  float sum_result[3]; // [esp+30h] [ebp-58h] BYREF
  float scaled_result[3]; // [esp+3Ch] [ebp-4Ch] BYREF
  float v14; // [esp+48h] [ebp-40h]
  int i; // [esp+4Ch] [ebp-3Ch]
  int v16; // [esp+50h] [ebp-38h]
  int v17; // [esp+54h] [ebp-34h]
  int v18; // [esp+58h] [ebp-30h]
  int v19; // [esp+5Ch] [ebp-2Ch]
  float scalar; // [esp+60h] [ebp-28h]
  char v21; // [esp+67h] [ebp-21h]
  float destination[3]; // [esp+68h] [ebp-20h] BYREF
  char v23; // [esp+77h] [ebp-11h]
  float v24; // [esp+78h] [ebp-10h]
  float v25; // [esp+7Ch] [ebp-Ch]
  float v26; // [esp+80h] [ebp-8h]
  bool v27; // [esp+87h] [ebp-1h]

  if ( !rf_geomod_face_query_segment_bounds_overlap((float *)this, a2 + 4, a2 + 7) )
    return 0;
  v26 = rf_vector_dot((float *)(this + 12), a2);
  if ( v26 == 0.0 )
    return 0;
  v25 = rf_vector_dot((float *)this, a2) + a2[3];
  scalar = -v25 / v26;
  if ( scalar <= -0.00009999999747378752 )
    return 0;
  v8 = fabs(scalar);
  v24 = v8;
  v21 = 0;
  v27 = 0;
  v23 = 0;
  v7 = rf_geomod_point_classify_against_face_plane((const float *)this, a2);
  switch ( v7 )
  {
    case 1:
      v27 = 1;
      break;
    case 2:
      if ( *(_DWORD *)(this + 36) )
      {
        v16 = 0;
        v17 = 0;
        v19 = 0;
        v18 = 0;
        for ( i = *(_DWORD *)(*(_DWORD *)(this + 36) + 64); i; i = v6 )
        {
          v5 = rf_geomod_point_classify_against_face_plane(*(const float **)i, a2);
          switch ( v5 )
          {
            case 1:
              ++v19;
              break;
            case 2:
              ++v17;
              break;
            case 3:
              ++v18;
              break;
          }
          ++v16;
          if ( *(_DWORD *)(i + 20) == *(_DWORD *)(*(_DWORD *)(this + 36) + 64) )
            v6 = 0;
          else
            v6 = *(_DWORD *)(i + 20);
        }
        if ( v17 == v16 )
        {
          v23 = 1;
          v14 = rf_vector_dot((float *)*(_DWORD *)(this + 36), a2);
          v27 = v14 < 0.0;
        }
        else
        {
          v27 = v19 > v18;
        }
      }
      else
      {
        v27 = 1;
      }
      break;
    case 3:
      v27 = 0;
      break;
  }
  if ( *(_DWORD *)(this + 40) )
  {
    if ( v24 <= *(float *)(this + 44) + 0.00009999999747378752 )
    {
      if ( v24 >= *(float *)(this + 44) - 0.00009999999747378752 )
      {
        if ( !*(_BYTE *)(this + 48) || v27 )
        {
          if ( !v27 || *(_BYTE *)(this + 48) )
          {
            if ( *(float *)(this + 44) > (double)v24 )
              v21 = 1;
          }
          else
          {
            v21 = 1;
          }
        }
      }
      else
      {
        v21 = 1;
      }
    }
  }
  else
  {
    v21 = 1;
  }
  if ( !v21 )
    return 0;
  rf_vector3_default_construct_noop(destination);
  v3 = rf_vector_multiply_scalar((const float *)(this + 12), scaled_result, scalar);
  v4 = rf_vector_add((const float *)this, sum_result, v3);
  rf_vector_copy(destination, copy_result, v4);
  if ( rf_geomod_face_contains_projected_point(a2, (char *)destination) )
  {
    if ( scalar > 0.00009999999747378752 && rf_geomod_face_hit_near_boundary(a2, destination) )
      return 1;
    ++*(_DWORD *)(this + 52);
    *(_DWORD *)(this + 40) = a2;
    *(float *)(this + 44) = v24;
    *(_BYTE *)(this + 48) = v27;
    *(_BYTE *)(this + 49) = v23;
    rf_vector_copy((float *)(this + 24), v10, destination);
  }
  return 0;
}

