// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00512C50 rf_projected_shadow_clip_solid_polygons
// UNREALRED VERIFIED [projected-shadow-receiver-20260903]: Solid-face counterpart of 0x00512A10. It walks the solid face collection through its alternate iterator, applies the same portal/0x44/Face+0x04 admission and six-plane clip, computes projector UV and view-fade alpha, optionally transforms surviving positions back from solid-local space, and emits every surviving polygon.
int __cdecl rf_projected_shadow_clip_solid_polygons(int a1, float *a2, void *a3, float *a4, float *a5)
{
  int result; // eax
  float *v6; // eax
  float *destination; // [esp+0h] [ebp-4Ch]
  int v8; // [esp+4h] [ebp-48h]
  float v9[3]; // [esp+8h] [ebp-44h] BYREF
  float out_vector[3]; // [esp+14h] [ebp-38h] BYREF
  float copy_result[3]; // [esp+20h] [ebp-2Ch] BYREF
  int v12; // [esp+2Ch] [ebp-20h]
  float v13; // [esp+30h] [ebp-1Ch]
  int k; // [esp+34h] [ebp-18h]
  int i; // [esp+38h] [ebp-14h]
  int j; // [esp+3Ch] [ebp-10h]
  float v17[3]; // [esp+40h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v17);
  result = rf_receiver_get_first_dword(a3);
  for ( i = result; i; i = result )
  {
    if ( !rf_face_is_portal((__int16 *)(i + 40))
      && (*(_DWORD *)(i + 40) & 0x44) == 0
      && *(float *)(i + 4) >= 0.1000000014901161 )
    {
      v12 = 0;
      for ( j = *(_DWORD *)(i + 64); j; j = v8 )
      {
        destination = (float *)((char *)&unk_928688 + 12 * v12++);
        rf_vector_copy(destination, copy_result, *(const float **)j);
        if ( *(_DWORD *)(j + 20) == *(_DWORD *)(i + 64) )
          v8 = 0;
        else
          v8 = *(_DWORD *)(j + 20);
      }
      ++unk_928418;
      v12 = rf_clip_polygon_against_planes(v12, (int)&unk_928688, (int)unk_928558, (int)a2, 6);
      if ( v12 )
      {
        for ( k = 0; k < v12; ++k )
        {
          v6 = rf_vector_subtract(&unk_928558[3 * k], out_vector, a2 + 24);
          rf_vector_copy(v17, v9, v6);
          rf_vector_rotate_by_matrix3(v17, a2 + 45);
          v13 = (a2[25] - a2[31]) * a2[65] * 2.0;
          unk_928428[3 * k] = v17[0] * a2[66] / v13 + 0.5;
          flt_92842C[3 * k] = v17[2] * a2[66] / v13 + 0.5;
          flt_92842C[3 * k + 1] = a2[67];
          if ( a4 )
          {
            rf_vector_rotate_by_matrix3(&unk_928558[3 * k], a5);
            rf_vector_accumulate(&unk_928558[3 * k], a4);
          }
        }
        rf_projected_shadow_emit_vertices(v12, (int)unk_928558, (int)unk_928428);
      }
    }
    result = rf_solid_face_next_link(i);
  }
  return result;
}

