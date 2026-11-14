// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00512A10 rf_projected_shadow_clip_polygon
// UNREALRED VERIFIED [general-gap-20260830]: Clips one candidate polygon against the projected volume, computes projected texture coordinates, carries the view-fade alpha, and forwards surviving geometry for vertex emission.
// UNREALRED VERIFIED [projected-shadow-receiver-20260903]: Iterates every face in one BSP-node face collection; rejects portals, Face+0x28 flags 0x04/0x40, and Face+0x04 values below 0.1; copies each complete cyclic vertex ring; clips it against all six projector planes; then computes UV/alpha and submits every surviving polygon.
// UNREALRED VERIFIED [projected-shadow-cone-20260903]: After six-plane clipping, subtracts the +3R cone point, rotates the survivor into the entity-oriented basis, and derives unclamped U/V from local X/Z, scale 1.65, and denominator 2*5.5R*(3-2*sqrt(2)).
int __cdecl rf_projected_shadow_clip_polygon(int a1, float *a2, void *a3, float *a4, float *a5)
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
    result = rf_face_next_spatial_node_link(i);
  }
  return result;
}

