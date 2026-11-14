// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00555DD0 rf_solid_transfer_primary_uvs_from_matching_key_face
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid boundary topology, generated UV modes, selection transforms and independently recovered routine boundaries): ECX solid plus sourceFace,translationXYZ,orientationMatrix, RET12. For every solid face with Face56 equal to source key, transforms each corner position by subtracting translation then inverse rotating into source coordinates. Attempts source projected-fan barycentric primary UV interpolation5331C0; on miss finds closest point on source edges, first strictly nearest retained, and interpolates edge U/V by distance-from-edge-start divided by edge length. Empty source or zero-length edge unguarded; no secondary UV writes, geometry rebuild, or rollback. Distances use original floating return helpers.
void __thiscall rf_solid_transfer_primary_uvs_from_matching_key_face(
        void *this,
        const void *a2,
        const float *a3,
        const float *a4)
{
  int v4; // [esp+0h] [ebp-64h]
  int v5; // [esp+4h] [ebp-60h]
  int v6; // [esp+8h] [ebp-5Ch]
  float copy_result[3]; // [esp+10h] [ebp-54h] BYREF
  float v8; // [esp+1Ch] [ebp-48h]
  float v9; // [esp+20h] [ebp-44h]
  float v10; // [esp+24h] [ebp-40h]
  float v11; // [esp+28h] [ebp-3Ch]
  int k; // [esp+2Ch] [ebp-38h]
  float source[3]; // [esp+30h] [ebp-34h] BYREF
  int v14; // [esp+3Ch] [ebp-28h]
  float v15; // [esp+40h] [ebp-24h]
  float destination[3]; // [esp+44h] [ebp-20h] BYREF
  float out_vector[3]; // [esp+50h] [ebp-14h] BYREF
  int j; // [esp+5Ch] [ebp-8h]
  int i; // [esp+60h] [ebp-4h]

  for ( i = rf_receiver_get_first_dword((char *)this + 112); i; i = rf_solid_face_next_link(i) )
  {
    if ( *(_DWORD *)(i + 56) == *((_DWORD *)a2 + 14) )
    {
      for ( j = *(_DWORD *)(i + 64); j; j = v6 )
      {
        rf_vector_subtract(*(const float **)j, out_vector, a3);
        rf_matrix3_inverse_rotate_vector(out_vector, (float *)a4);
        if ( !rf_face_interpolate_primary_uv_projected_fan(
                (float **)a2,
                (int)out_vector,
                (float *)(j + 4),
                (float *)(j + 8)) )
        {
          k = *((_DWORD *)a2 + 16);
          v14 = k;
          rf_vector3_default_construct_noop(source);
          rf_vector3_closest_point_on_segment(out_vector, *(const float **)k, **(const float ***)(k + 20), source);
          v15 = rf_vector_distance(source, out_vector);
          rf_vector3_copy_return_destination(destination, source);
          if ( *(_DWORD *)(k + 20) == *((_DWORD *)a2 + 16) )
            v5 = 0;
          else
            v5 = *(_DWORD *)(k + 20);
          for ( k = v5; k; k = v4 )
          {
            rf_vector3_closest_point_on_segment(out_vector, *(const float **)k, **(const float ***)(k + 20), source);
            v8 = rf_vector_distance(source, out_vector);
            if ( v15 > (double)v8 )
            {
              rf_vector_copy(destination, copy_result, source);
              v14 = k;
              v15 = v8;
            }
            if ( *(_DWORD *)(k + 20) == *((_DWORD *)a2 + 16) )
              v4 = 0;
            else
              v4 = *(_DWORD *)(k + 20);
          }
          v9 = rf_vector_distance(destination, (const float *)*(_DWORD *)v14);
          v11 = rf_vector_distance((const float *)*(_DWORD *)v14, (const float *)**(_DWORD **)(v14 + 20));
          v10 = v9 / v11;
          *(float *)(j + 4) = (1.0 - v10) * *(float *)(v14 + 4) + v10 * *(float *)(*(_DWORD *)(v14 + 20) + 4);
          *(float *)(j + 8) = (1.0 - v10) * *(float *)(v14 + 8) + v10 * *(float *)(*(_DWORD *)(v14 + 20) + 8);
        }
        if ( *(_DWORD *)(j + 20) == *(_DWORD *)(i + 64) )
          v6 = 0;
        else
          v6 = *(_DWORD *)(j + 20);
      }
    }
  }
}

