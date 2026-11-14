// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581970 rf_renderer_screen_point_to_world_ray
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, volume segment integration, clipping, renderer bridges and original call sites): Writes6-float(origin,direction) from screenXY using center/half-size globals18CD1C8/18CD290 and projection scale3C4/3BC/3C0. Perspective byte663F39 nonzero:local((x-cx)/cx*scaleX,-(y-cy)/cy*scaleY,1),normalize,rotate by camera matrix18CD398;origin=camera18CD4A8. Orthographic:local sameXY,z0 without normalization,rotate then origin=camera+offset,direction=forward18CD3B0. No half-pixel adjustment,viewport clipping or divisor checks;direction not scaled by far distance. Existing nominal int return is final vector-copy helper result,not separate status.
float *__cdecl rf_renderer_screen_point_to_world_ray(float *destination, float a2, float a3)
{
  float *v4; // eax
  float v5[3]; // [esp+0h] [ebp-54h] BYREF
  float v6[3]; // [esp+Ch] [ebp-48h] BYREF
  float sum_result[3]; // [esp+18h] [ebp-3Ch] BYREF
  float v8[3]; // [esp+24h] [ebp-30h] BYREF
  float copy_result[3]; // [esp+30h] [ebp-24h] BYREF
  float rhs; // [esp+3Ch] [ebp-18h] BYREF
  float v11; // [esp+40h] [ebp-14h]
  float v12; // [esp+44h] [ebp-10h]
  float source; // [esp+48h] [ebp-Ch] BYREF
  float v14; // [esp+4Ch] [ebp-8h]
  float v15; // [esp+50h] [ebp-4h]

  if ( byte_663F39 )
  {
    rf_vector3_default_construct_noop(&source);
    source = (a2 - unk_18CD1C8) / unk_18CD1C8;
    v14 = -(a3 - unk_18CD290) / unk_18CD290;
    v15 = 1.0;
    source = source * unk_18CD3C4 / unk_18CD3BC;
    v14 = v14 * unk_18CD3C4 / unk_18CD3C0;
    rf_vector_normalize_reciprocal_sqrt(&source);
    rf_vector_rotate_by_matrix3(&source, unk_18CD398);
    rf_vector_copy(destination, copy_result, unk_18CD4A8);
    return rf_vector_copy(destination + 3, v8, &source);
  }
  else
  {
    rf_vector3_default_construct_noop(&rhs);
    rhs = (a2 - unk_18CD1C8) / unk_18CD1C8;
    v11 = -(a3 - unk_18CD290) / unk_18CD290;
    v12 = 0.0;
    rhs = rhs * unk_18CD3C4 / unk_18CD3BC;
    v11 = v11 * unk_18CD3C4 / unk_18CD3C0;
    rf_vector_rotate_by_matrix3(&rhs, unk_18CD398);
    v4 = rf_vector_add(unk_18CD4A8, sum_result, &rhs);
    rf_vector_copy(destination, v6, v4);
    return rf_vector_copy(destination + 3, v5, &flt_18CD3B0);
  }
}

