// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005297F0 rf_renderer_accumulate_active_light_rgb
// VERIFIED: Non-world point/spot contribution helper. Spot angular interpolation is linear by default and is squared only when renderer byte +0x4E is set. RFL runtime creation passes zero for that optional flag.
// UNREALRED VERIFIED [rfl-light-decode]: Accumulates non-world point/spot contribution using the decoded attenuation selector and optional squared spot angular factor.
// UNREALRED VERIFIED [nonworld-byte-rgb-20260903]: Corrected scope: iterates active light records of types 1 through 4, applies their type-specific directional, point, spot, or tube contribution rules and optional per-light byte weights, and accumulates floating RGB. The former point/spot-only name was incomplete.
float *__cdecl rf_renderer_accumulate_active_light_rgb(
        float *a1,
        float *a2,
        float *a3,
        float *a4,
        float *a5,
        int a6,
        int a7,
        _BYTE *a8)
{
  float *result; // eax
  float *v9; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float v14[3]; // [esp+1Ch] [ebp-158h] BYREF
  float v15[3]; // [esp+28h] [ebp-14Ch] BYREF
  float v16[3]; // [esp+34h] [ebp-140h] BYREF
  float v17[3]; // [esp+40h] [ebp-134h] BYREF
  float sum_result[3]; // [esp+4Ch] [ebp-128h] BYREF
  float scaled_result[3]; // [esp+58h] [ebp-11Ch] BYREF
  float v20[3]; // [esp+64h] [ebp-110h] BYREF
  float v21[3]; // [esp+70h] [ebp-104h] BYREF
  float v22[3]; // [esp+7Ch] [ebp-F8h] BYREF
  float v23[3]; // [esp+88h] [ebp-ECh] BYREF
  float v24[3]; // [esp+94h] [ebp-E0h] BYREF
  float v25[3]; // [esp+A0h] [ebp-D4h] BYREF
  float v26[3]; // [esp+ACh] [ebp-C8h] BYREF
  float copy_result[3]; // [esp+B8h] [ebp-BCh] BYREF
  float v28; // [esp+C4h] [ebp-B0h]
  float v29; // [esp+C8h] [ebp-ACh]
  float v30; // [esp+CCh] [ebp-A8h]
  float v31; // [esp+D0h] [ebp-A4h]
  float v32; // [esp+D4h] [ebp-A0h]
  float v33[3]; // [esp+D8h] [ebp-9Ch] BYREF
  int v34; // [esp+E4h] [ebp-90h] BYREF
  int v35; // [esp+E8h] [ebp-8Ch] BYREF
  float v36[3]; // [esp+ECh] [ebp-88h] BYREF
  int v37; // [esp+F8h] [ebp-7Ch] BYREF
  float v38; // [esp+FCh] [ebp-78h]
  float v39[3]; // [esp+100h] [ebp-74h] BYREF
  float scalar; // [esp+10Ch] [ebp-68h]
  float out_vector[3]; // [esp+110h] [ebp-64h] BYREF
  float length; // [esp+11Ch] [ebp-58h]
  float destination[3]; // [esp+120h] [ebp-54h] BYREF
  float v44; // [esp+12Ch] [ebp-48h]
  float lhs[3]; // [esp+130h] [ebp-44h] BYREF
  float v46; // [esp+13Ch] [ebp-38h]
  int v47; // [esp+140h] [ebp-34h] BYREF
  int v48; // [esp+144h] [ebp-30h] BYREF
  float v49; // [esp+148h] [ebp-2Ch]
  float v50; // [esp+14Ch] [ebp-28h]
  float rhs[3]; // [esp+150h] [ebp-24h] BYREF
  float v52; // [esp+15Ch] [ebp-18h]
  float v53; // [esp+160h] [ebp-14h]
  unsigned __int8 v54; // [esp+167h] [ebp-Dh]
  float v55; // [esp+168h] [ebp-Ch]
  float *i; // [esp+16Ch] [ebp-8h]
  int v57; // [esp+170h] [ebp-4h]

  if ( !dword_663B0C && rf_renderer_lights_enabled )
  {
    unk_D03604 += rf_light_active_world_count;
    ++unk_D03600;
    for ( i = nullptr; ; i = (float *)((char *)i + 1) )
    {
      result = i;
      if ( (int)i >= (int)rf_light_active_world_count )
        break;
      v57 = rf_light_active_world_records[(_DWORD)i];
      if ( a6 )
        v54 = *(_BYTE *)(*(_DWORD *)(a6 + 4 * (_DWORD)i) + a7);
      else
        v54 = -1;
      if ( v54 )
      {
        rf_vector3_default_construct_noop(rhs);
        v55 = (double)v54 / 255.0;
        v52 = *(float *)(v57 + 64) * v55;
        v50 = *(float *)(v57 + 68) * v55;
        v53 = *(float *)(v57 + 72) * v55;
        if ( unk_18CD388 )
          rf_vector_copy(rhs, v26, (const float *)(v57 + 92));
        else
          rf_vector_copy(rhs, copy_result, (const float *)(v57 + 12));
        switch ( *(_DWORD *)(v57 + 8) )
        {
          case 1:
            if ( a5 )
              v49 = rf_vector_dot(rhs, a5) * flt_663B28;
            else
              v49 = flt_663B28;
            if ( v49 > 0.0 )
            {
              *a1 = v52 * v49 + *a1;
              *a2 = v50 * v49 + *a2;
              *a3 = v53 * v49 + *a3;
            }
            break;
          case 2:
            if ( a5 )
            {
              rf_renderer_compute_point_light_surface_terms(
                a4,
                (int)a5,
                rhs,
                *(float *)(v57 + 60),
                a8,
                (float *)&v48,
                (float *)&v47);
            }
            else
            {
              *(float *)&v47 = rf_renderer_light_distance_and_direction(a4, rhs, nullptr);
              *(float *)&v48 = *(float *)&v47 * 0.1000000014901161;
            }
            if ( *(float *)&v48 > 0.0 && *(float *)(v57 + 60) > (double)*(float *)&v47 )
            {
              v46 = rf_nonworld_light_attenuation_functions[*(_DWORD *)(v57 + 84)](*(float *)&v47, *(float *)(v57 + 60));
              v46 = v46 * *(float *)&v48;
              *a1 = v52 * v46 + *a1;
              *a2 = v50 * v46 + *a2;
              *a3 = v53 * v46 + *a3;
            }
            break;
          case 3:
            rf_vector3_default_construct_noop(v36);
            if ( unk_18CD388 )
              rf_vector_copy(v36, v14, (const float *)(v57 + 116));
            else
              rf_vector_copy(v36, v15, (const float *)(v57 + 36));
            if ( a5 )
            {
              rf_renderer_compute_spot_light_surface_terms(
                a4,
                (int)a5,
                rhs,
                (int)v36,
                *(float *)(v57 + 60),
                a8,
                (float *)&v37,
                (float *)&v34,
                (float *)&v35);
            }
            else
            {
              rf_vector3_default_construct_noop(v33);
              *(float *)&v35 = rf_renderer_light_distance_and_direction(a4, rhs, v33);
              *(float *)&v37 = *(float *)&v35 * 0.1000000014901161;
              *(float *)&v34 = rf_vector_dot(v33, v36);
            }
            if ( *(float *)&v37 > 0.0
              && *(float *)(v57 + 60) > (double)*(float *)&v35
              && *(float *)(v57 + 136) > (double)*(float *)&v34 )
            {
              *(float *)&v35 = (1.0 - *(float *)(v57 + 56)) * *(float *)&v35;
              v30 = rf_nonworld_light_attenuation_functions[*(_DWORD *)(v57 + 84)](*(float *)&v35, *(float *)(v57 + 60));
              if ( *(float *)(v57 + 132) <= (double)*(float *)&v34 )
              {
                v29 = *(float *)&v34 - *(float *)(v57 + 132);
                v28 = *(float *)(v57 + 136) - *(float *)(v57 + 132);
                v31 = 1.0 - v29 / v28;
                if ( *(_BYTE *)(v57 + 78) )
                  v31 = v31 * v31;
              }
              else
              {
                v31 = 1.0;
              }
              v32 = *(float *)&v37 * v30 * v31;
              *a1 = v52 * v32 + *a1;
              *a2 = v50 * v32 + *a2;
              *a3 = v53 * v32 + *a3;
            }
            break;
          case 4:
            rf_vector3_default_construct_noop(lhs);
            if ( unk_18CD388 )
              rf_vector_copy(lhs, v24, (const float *)(v57 + 104));
            else
              rf_vector_copy(lhs, v25, (const float *)(v57 + 24));
            rf_vector3_default_construct_noop(destination);
            rf_vector_subtract(lhs, out_vector, rhs);
            length = rf_vector_normalize_get_length(out_vector);
            rf_vector_subtract(a4, v39, rhs);
            scalar = rf_vector_dot(out_vector, v39);
            if ( scalar >= 0.0 )
            {
              if ( length >= (double)scalar )
              {
                v11 = rf_vector_multiply_scalar(out_vector, scaled_result, scalar);
                v12 = rf_vector_add(rhs, sum_result, v11);
                v13 = rf_vector_subtract(v12, v17, a4);
                rf_vector_copy(destination, v16, v13);
              }
              else
              {
                v10 = rf_vector_subtract(lhs, v21, a4);
                rf_vector_copy(destination, v20, v10);
              }
            }
            else
            {
              v9 = rf_vector_subtract(rhs, v23, a4);
              rf_vector_copy(destination, v22, v9);
            }
            v44 = rf_vector3_length(destination);
            if ( *(float *)(v57 + 60) > (double)v44 )
            {
              v38 = rf_nonworld_light_attenuation_functions[*(_DWORD *)(v57 + 84)](v44, *(float *)(v57 + 60));
              *a1 = v52 * v38 + *a1;
              *a2 = v50 * v38 + *a2;
              *a3 = v53 * v38 + *a3;
            }
            break;
          default:
            continue;
        }
      }
    }
  }
  else
  {
    *a3 = 1.0;
    *a2 = 1.0;
    *a1 = 1.0;
    return a3;
  }
  return result;
}

