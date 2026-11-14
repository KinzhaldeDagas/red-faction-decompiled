// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052A1E0 rf_renderer_compute_mesh_vertex_specular_rgb8
// VERIFIED: Non-world/object light RGB helper. It gates on global lighting, sums eligible active contributions, normalizes all accumulated channels only when the maximum RGB channel exceeds 1, then quantizes RGB to bytes.
// UNREALRED VERIFIED [rfl-light-decode]: Accumulates object lighting, max-channel normalizes values above one, and emits byte RGB.
// UNREALRED VERIFIED [nonworld-byte-rgb-20260903]: Corrected role: computes per-vertex mesh specular RGB8 from active point and spot lights. Point weight is caller strength times squared radial falloff times squared thresholded reflection alignment; spot weight uses selected attenuation times linear cone interpolation times the same squared alignment. It max-channel normalizes above one, multiplies by 255, and truncates toward zero. Its return flag is set only by a nonzero point-light highlight, even though spot RGB is accumulated.
// UNREALRED VERIFIED [v3d-specular-fields-20260903]: Resolves the former V3D unknown floats exactly. Runtime material +0x84 is specular strength. Field +0x88 is the reflection-alignment cutoff c. Point and spot branches both form response=max((dot(R,V)-c)/(1-c),0)^2 and multiply it by strength; their radial/cone attenuation terms are applied separately.
char __cdecl rf_renderer_compute_mesh_vertex_specular_rgb8(
        float *rhs,
        float *a2,
        _BYTE *a3,
        _BYTE *a4,
        _BYTE *a5,
        float a6,
        float a7,
        char a8)
{
  float *v8; // eax
  float *v10; // eax
  float *v11; // eax
  float *v12; // eax
  float *v13; // eax
  float *v14; // eax
  float *v15; // eax
  float *v16; // eax
  float scalar; // [esp+Ch] [ebp-160h]
  int scalara; // [esp+Ch] [ebp-160h]
  float v19; // [esp+14h] [ebp-158h]
  float v20; // [esp+18h] [ebp-154h]
  int v21; // [esp+1Ch] [ebp-150h]
  float v22[3]; // [esp+20h] [ebp-14Ch] BYREF
  float v23[3]; // [esp+2Ch] [ebp-140h] BYREF
  int v24[3]; // [esp+38h] [ebp-134h] BYREF
  float v25[3]; // [esp+44h] [ebp-128h] BYREF
  float v26[3]; // [esp+50h] [ebp-11Ch] BYREF
  float v27[3]; // [esp+5Ch] [ebp-110h] BYREF
  float scaled_result[3]; // [esp+68h] [ebp-104h] BYREF
  int v29[3]; // [esp+74h] [ebp-F8h] BYREF
  float v30[3]; // [esp+80h] [ebp-ECh] BYREF
  float v31[3]; // [esp+8Ch] [ebp-E0h] BYREF
  float v32[3]; // [esp+98h] [ebp-D4h] BYREF
  float copy_result[3]; // [esp+A4h] [ebp-C8h] BYREF
  float out_vector[3]; // [esp+B0h] [ebp-BCh] BYREF
  float v35; // [esp+BCh] [ebp-B0h]
  float v36; // [esp+C0h] [ebp-ACh]
  float v37; // [esp+C4h] [ebp-A8h]
  float v38[3]; // [esp+C8h] [ebp-A4h] BYREF
  float v39; // [esp+D4h] [ebp-98h]
  float v40; // [esp+D8h] [ebp-94h]
  float v41[3]; // [esp+DCh] [ebp-90h] BYREF
  float v42; // [esp+E8h] [ebp-84h]
  float v43[3]; // [esp+ECh] [ebp-80h] BYREF
  int v44; // [esp+F8h] [ebp-74h] BYREF
  int v45; // [esp+FCh] [ebp-70h] BYREF
  float v46[3]; // [esp+100h] [ebp-6Ch] BYREF
  int v47; // [esp+10Ch] [ebp-60h] BYREF
  float v48; // [esp+110h] [ebp-5Ch]
  float v49[3]; // [esp+114h] [ebp-58h] BYREF
  float v50; // [esp+120h] [ebp-4Ch]
  float destination[3]; // [esp+124h] [ebp-48h] BYREF
  float v52; // [esp+130h] [ebp-3Ch]
  float v53; // [esp+134h] [ebp-38h]
  float lhs[3]; // [esp+138h] [ebp-34h] BYREF
  float v55; // [esp+144h] [ebp-28h]
  float v56[3]; // [esp+148h] [ebp-24h] BYREF
  int v57; // [esp+154h] [ebp-18h]
  float v58; // [esp+158h] [ebp-14h]
  float v59; // [esp+15Ch] [ebp-10h]
  char v60; // [esp+163h] [ebp-9h]
  float v61; // [esp+164h] [ebp-8h]
  signed int i; // [esp+168h] [ebp-4h]

  v60 = 0;
  v8 = rf_vector_subtract(&flt_18CD5E8, out_vector, rhs);
  rf_vector3_normalized_copy_unchecked(v8, (int)v56);
  v59 = 0.0;
  v58 = 0.0;
  v61 = 0.0;
  if ( !dword_663B0C && rf_renderer_lights_enabled )
  {
    unk_D03604 += rf_light_active_world_count;
    ++unk_D03600;
    for ( i = 0; i < (int)rf_light_active_world_count; ++i )
    {
      v57 = rf_light_active_world_records[i];
      if ( *(_BYTE *)(v57 + 76) && (!*(_BYTE *)(v57 + 77) || a8) )
      {
        rf_vector3_default_construct_noop(lhs);
        if ( unk_18CD388 )
          rf_vector_copy(lhs, v32, (const float *)(v57 + 92));
        else
          rf_vector_copy(lhs, copy_result, (const float *)(v57 + 12));
        v21 = *(_DWORD *)(v57 + 8);
        if ( v21 == 2 )
        {
          rf_vector3_default_construct_noop(destination);
          v10 = rf_vector_subtract(lhs, v31, rhs);
          rf_vector_copy(destination, v30, v10);
          v52 = rf_vector3_length(destination);
          if ( *(float *)(v57 + 60) > (double)v52 )
          {
            v53 = a2 ? rf_vector_dot(a2, destination) : rf_vector3_length(destination) * 0.1000000014901161;
            if ( v53 > 0.0 )
            {
              if ( v52 > 0.0 )
                v53 = v53 / v52;
              if ( *(float *)(v57 + 60) > (double)v52 )
              {
                v48 = (*(float *)(v57 + 60) - v52) / *(float *)(v57 + 60);
                v48 = v48 * v48;
                rf_vector3_normalized_copy_unchecked(destination, (int)v49);
                scalar = rf_vector_dot(a2, v49);
                v11 = rf_vector_scale((float *)v29, 2.0, a2);
                v12 = rf_vector_multiply_scalar(v11, scaled_result, scalar);
                v13 = rf_vector_subtract(v12, v27, v49);
                v50 = rf_vector_dot(v13, v56);
                v50 = v50 - a7;
                v50 = 1.0 / (1.0 - a7) * v50;
                v50 = rf_float_maximum_two_values(v50, 0.0);
                if ( v50 != 0.0 )
                {
                  v50 = v50 * v50;
                  v50 = a6 * v48 * v50;
                  v59 = *(float *)(v57 + 64) * v50 + v59;
                  v58 = *(float *)(v57 + 68) * v50 + v58;
                  v61 = *(float *)(v57 + 72) * v50 + v61;
                  v60 = 1;
                }
              }
            }
          }
        }
        else if ( v21 == 3 )
        {
          rf_vector3_default_construct_noop(v46);
          if ( unk_18CD388 )
            rf_vector_copy(v46, v25, (const float *)(v57 + 116));
          else
            rf_vector_copy(v46, v26, (const float *)(v57 + 36));
          if ( a2 )
          {
            rf_renderer_compute_spot_light_surface_terms(
              rhs,
              a2,
              lhs,
              v46,
              *(float *)(v57 + 60),
              nullptr,
              (float *)&v47,
              (float *)&v44,
              (float *)&v45);
          }
          else
          {
            rf_vector3_default_construct_noop(v43);
            *(float *)&v45 = rf_renderer_light_distance_and_direction(rhs, lhs, v43);
            *(float *)&v47 = *(float *)&v45 * 0.1000000014901161;
            *(float *)&v44 = rf_vector_dot(v43, v46);
          }
          if ( *(float *)&v47 > 0.0
            && *(float *)(v57 + 60) > (double)*(float *)&v45
            && *(float *)(v57 + 136) > (double)*(float *)&v44 )
          {
            *(float *)&v45 = (1.0 - *(float *)(v57 + 56)) * *(float *)&v45;
            v39 = rf_nonworld_light_attenuation_functions[*(_DWORD *)(v57 + 84)](*(float *)&v45, *(float *)(v57 + 60));
            if ( *(float *)(v57 + 132) <= (double)*(float *)&v44 )
            {
              v37 = *(float *)&v44 - *(float *)(v57 + 132);
              v36 = *(float *)(v57 + 136) - *(float *)(v57 + 132);
              v40 = 1.0 - v37 / v36;
            }
            else
            {
              v40 = 1.0;
            }
            rf_vector_subtract(lhs, v38, rhs);
            rf_vector3_normalized_copy_unchecked(v38, (int)v41);
            scalara = v47;
            v14 = rf_vector_scale((float *)v24, 2.0, a2);
            v15 = rf_vector_multiply_scalar(v14, v23, *(float *)&scalara);
            v16 = rf_vector_subtract(v15, v22, v41);
            v42 = rf_vector_dot(v16, v56);
            v42 = v42 - a7;
            v42 = 1.0 / (1.0 - a7) * v42;
            v42 = rf_float_maximum_two_values(v42, 0.0);
            if ( v42 != 0.0 )
            {
              v42 = v42 * v42;
              v42 = a6 * v39 * v40 * v42;
              v59 = *(float *)(v57 + 64) * v42 + v59;
              v58 = *(float *)(v57 + 68) * v42 + v58;
              v61 = *(float *)(v57 + 72) * v42 + v61;
            }
          }
        }
      }
    }
    v20 = v61;
    v19 = rf_float_maximum_two_values(v59, v58);
    v55 = rf_float_maximum_two_values(v19, v20);
    if ( v55 > 1.0 )
    {
      v35 = 1.0 / v55;
      v59 = v59 * v35;
      v58 = v58 * v35;
      v61 = v61 * v35;
    }
    *a3 = (int)(v59 * 255.0);
    *a4 = (int)(v58 * 255.0);
    *a5 = (int)(v61 * 255.0);
    return v60;
  }
  else
  {
    *a3 = 0;
    *a4 = 0;
    *a5 = 0;
    return 0;
  }
}

