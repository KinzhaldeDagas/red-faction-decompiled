// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581560 rf_clip_planes_build_instance_subset_for_sphere
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered cdecl center3f,radius. Clears output count18CD100. For each current28-byte world clip record at18CD3C8,keeps plane iff signedDistance(center)>-radius (strict;not a sphere-reject test). Copies tag byte and both DWORD support selectors into next28-byte output record18CD4D8. Let T(v)=row-transform(v,instance matrix18CD5B8),C=camera18CD4A8,I=instance origin18CD804. Output normal=T(source normal);point=T(C-I) except tag EXACTLY2 uses T(C-I+forward18CD7F8*farDistance18CD36C). Constructs output plane(n,-dot(n,point)),increments count. Ignores original plane scalar when constructing output;copied selectors are not recomputed after normal transform. Finally sets outcode-enable byte663F38=FF. No output
// capacity,radius,orthogonality or finite checks;global mutable scratch.
void __cdecl rf_clip_planes_build_instance_subset_for_sphere(const float *a1, float a2)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *scalar; // [esp+0h] [ebp-74h]
  float *v7; // [esp+8h] [ebp-6Ch]
  float v8[3]; // [esp+Ch] [ebp-68h] BYREF
  float v9[3]; // [esp+18h] [ebp-5Ch] BYREF
  float v10[3]; // [esp+24h] [ebp-50h] BYREF
  float v11[3]; // [esp+30h] [ebp-44h] BYREF
  float v12[3]; // [esp+3Ch] [ebp-38h] BYREF
  float sum_result[3]; // [esp+48h] [ebp-2Ch] BYREF
  float scaled_result[3]; // [esp+54h] [ebp-20h] BYREF
  float out_vector[3]; // [esp+60h] [ebp-14h] BYREF
  float v16; // [esp+6Ch] [ebp-8h]
  int i; // [esp+70h] [ebp-4h]

  dword_18CD100 = 0;
  for ( i = 0; i < dword_18CD390; ++i )
  {
    v16 = rf_plane_point_signed_distance((float *)&unk_18CD3CC + 7 * i, (float *)a1);
    if ( v16 > 0.0 - a2 )
    {
      byte_18CD4D8[28 * dword_18CD100] = byte_18CD3C8[28 * i];
      dword_18CD4EC[7 * dword_18CD100] = dword_18CD3DC[7 * i];
      dword_18CD4F0[7 * dword_18CD100] = dword_18CD3E0[7 * i];
      if ( byte_18CD3C8[28 * i] == 2 )
      {
        scalar = rf_vector_multiply_scalar(&flt_18CD7F8, scaled_result, flt_18CD36C);
        v2 = rf_vector_subtract(unk_18CD4A8, out_vector, unk_18CD804);
        v3 = rf_vector_add(v2, sum_result, scalar);
        v7 = rf_vector3_transform_by_matrix_rows(v3, v12, &flt_18CD5B8);
        v4 = rf_vector3_transform_by_matrix_rows((float *)&unk_18CD3CC + 7 * i, v11, &flt_18CD5B8);
      }
      else
      {
        v5 = rf_vector_subtract(unk_18CD4A8, v10, unk_18CD804);
        v7 = rf_vector3_transform_by_matrix_rows(v5, v9, &flt_18CD5B8);
        v4 = rf_vector3_transform_by_matrix_rows((float *)&unk_18CD3CC + 7 * i, v8, &flt_18CD5B8);
      }
      rf_plane4_construct_normal_point((float *)&unk_18CD4DC + 7 * dword_18CD100, v4, v7);
      ++dword_18CD100;
    }
  }
  byte_663F38 = -1;
}

