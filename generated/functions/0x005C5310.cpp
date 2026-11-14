// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C5310 rf_renderer_transform_world_points_to_clip48
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): Transforms count contiguous input XYZ vectors into output records of stride48: subtract current camera origin18CD5E8, multiply by rows of scaled camera matrix18CD4B4, store camera XYZ, clear flags byte+25, refresh camera outcode. Orthographic branch overrides output Z with depth constant18CD380 before outcode. Does not project screen XY, initialize other vertex fields or check pointers/capacities. Loop is while(count--), so negative count is unsafe. Inferred char return is incidental, varying with mode/count/last outcode.
char __cdecl rf_renderer_transform_world_points_to_clip48(float *a1, float *lhs, int a3)
{
  int v3; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float v10[3]; // [esp+0h] [ebp-6Ch] BYREF
  float v11[3]; // [esp+Ch] [ebp-60h] BYREF
  float v12[3]; // [esp+18h] [ebp-54h] BYREF
  float v13[3]; // [esp+24h] [ebp-48h] BYREF
  float v14[3]; // [esp+30h] [ebp-3Ch] BYREF
  float v15[3]; // [esp+3Ch] [ebp-30h] BYREF
  float copy_result[3]; // [esp+48h] [ebp-24h] BYREF
  float out_vector[3]; // [esp+54h] [ebp-18h] BYREF
  float destination[3]; // [esp+60h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(destination);
  LOBYTE(v3) = byte_663F39;
  if ( byte_663F39 )
  {
    while ( 1 )
    {
      v3 = a3--;
      if ( !v3 )
        break;
      v7 = rf_vector_subtract(lhs, v13, &flt_18CD5E8);
      rf_vector_copy(destination, v12, v7);
      v8 = rf_vector3_transform_by_matrix_rows(destination, v11, &flt_18CD4B4);
      rf_vector_copy(a1, v10, v8);
      *((_BYTE *)a1 + 25) = 0;
      rf_clip_vertex_update_camera_outcode((int)a1);
      lhs += 3;
      a1 += 12;
    }
  }
  else
  {
    while ( a3-- )
    {
      v5 = rf_vector_subtract(lhs, out_vector, &flt_18CD5E8);
      rf_vector_copy(destination, copy_result, v5);
      v6 = rf_vector3_transform_by_matrix_rows(destination, v15, &flt_18CD4B4);
      rf_vector_copy(a1, v14, v6);
      a1[2] = unk_18CD380;
      *((_BYTE *)a1 + 25) = 0;
      LOBYTE(v3) = rf_clip_vertex_update_camera_outcode((int)a1);
      lhs += 3;
      a1 += 12;
    }
  }
  return v3;
}

