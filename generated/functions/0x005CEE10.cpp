// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CEE10 rf_v3c_asset_collide_static_mesh
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Thiscall(asset144/148,meshIndex,query104,hit32,resetByte). Mesh array at asset+76,stride144;LOD table at mesh+140,selected geometry=table[table[0]],but geometry flag+64 mask0x10 forces table[1]/firstLOD. Reset only when byte EXACT1: hit.fraction0=1,tag+28=0;other fields unchanged. Query layout: reference translation0,row matrix12,input start48,delta60,radius72,flags76,working start80/delta92. If flags2 set,copies input coordinates to work;otherwise subtracts reference translation then dots start/delta with matrix rows. Subtracts mesh table translation+28 from working start;tests segment to start+delta against table bounds+44/+56 expanded by radius. Iterates geometry batches56 (count uint16+12,pointer+8),triangle countuint16
// batch+42,index/flag8-byte records batch+20;flag0x20 enables two-sided test. Dispatches ray/sphere;flag1 returns first accepted traversal hit. On success adds ONLY mesh translation to hit point;does not transform point/normal back through query matrix/reference origin. Shared query fields mutated,no mesh/index/LOD/triangle bounds validation.
char __thiscall rf_v3c_asset_collide_static_mesh(void *this, int a2, void *rhs, void *a4, unsigned __int8 a5)
{
  float *v5; // eax
  float *lod_table_translation; // eax
  float *lod_table_bounds_min; // eax
  float *lod_table_bounds_max; // eax
  char v10; // bl
  float *v11; // eax
  float *v12; // eax
  float v13; // [esp+0h] [ebp-D4h]
  float v14; // [esp+0h] [ebp-D4h]
  float v15[3]; // [esp+Ch] [ebp-C8h] BYREF
  float v16[3]; // [esp+18h] [ebp-BCh] BYREF
  float v17[3]; // [esp+24h] [ebp-B0h] BYREF
  float v18[3]; // [esp+30h] [ebp-A4h] BYREF
  float v19[3]; // [esp+3Ch] [ebp-98h] BYREF
  float v20[3]; // [esp+48h] [ebp-8Ch] BYREF
  float v21[3]; // [esp+54h] [ebp-80h] BYREF
  float out_vector[3]; // [esp+60h] [ebp-74h] BYREF
  float v23[3]; // [esp+6Ch] [ebp-68h] BYREF
  float copy_result[3]; // [esp+78h] [ebp-5Ch] BYREF
  int v25; // [esp+84h] [ebp-50h]
  int j; // [esp+88h] [ebp-4Ch]
  _DWORD *v27; // [esp+8Ch] [ebp-48h]
  int i; // [esp+90h] [ebp-44h]
  int v29; // [esp+94h] [ebp-40h]
  float sum_result[3]; // [esp+98h] [ebp-3Ch] BYREF
  char v31; // [esp+A7h] [ebp-2Dh]
  float v32[3]; // [esp+A8h] [ebp-2Ch] BYREF
  _DWORD *v33; // [esp+B4h] [ebp-20h]
  _DWORD *v34; // [esp+B8h] [ebp-1Ch]
  int v35[3]; // [esp+BCh] [ebp-18h] BYREF
  int v36[3]; // [esp+C8h] [ebp-Ch] BYREF

  v31 = 0;
  v34 = (_DWORD *)(*((_DWORD *)this + 19) + 144 * a2);
  v33 = *(_DWORD **)(*((_DWORD *)this + 19) + 144 * a2 + 140);
  v29 = v33[*v33];
  if ( (*(_DWORD *)(v29 + 64) & 0x10) != 0 )
    v29 = v33[1];
  if ( a5 == 1 )
  {
    *(float *)a4 = 1.0;
    *((_DWORD *)a4 + 7) = 0;
  }
  if ( (*((_DWORD *)rhs + 19) & 2) != 0 )
  {
    rf_vector_copy((float *)rhs + 20, copy_result, (const float *)rhs + 12);
    rf_vector_copy((float *)rhs + 23, v23, (const float *)rhs + 15);
  }
  else
  {
    v5 = rf_vector_subtract((const float *)rhs + 12, out_vector, (const float *)rhs);
    rf_vector_copy((float *)rhs + 20, v21, v5);
    rf_matrix3_inverse_rotate_vector((float *)rhs + 20, (float *)rhs + 3);
    rf_vector_copy((float *)rhs + 23, v20, (const float *)rhs + 15);
    rf_matrix3_inverse_rotate_vector((float *)rhs + 23, (float *)rhs + 3);
  }
  lod_table_translation = rf_model_mesh144_get_lod_table_translation(v34, v19);
  rf_vector_subtract_in_place((float *)rhs + 20, lod_table_translation);
  v13 = *((float *)rhs + 18);
  lod_table_bounds_min = rf_model_mesh144_get_lod_table_bounds_min(v34, v18);
  rf_vector3_subtract_scalar_from_components(lod_table_bounds_min, (float *)v36, v13);
  v14 = *((float *)rhs + 18);
  lod_table_bounds_max = rf_model_mesh144_get_lod_table_bounds_max(v34, v17);
  rf_vector3_add_scalar_to_components(lod_table_bounds_max, (float *)v35, v14);
  rf_vector_add((const float *)rhs + 20, sum_result, (const float *)rhs + 23);
  rf_vector3_default_construct_noop(v32);
  if ( !rf_segment_intersects_aabb((float *)v36, (float *)v35, (float *)rhs + 20, sum_result, v32) )
    return 0;
  for ( i = 0; i < *(unsigned __int16 *)(v29 + 12); ++i )
  {
    v27 = (_DWORD *)(*(_DWORD *)(v29 + 8) + 56 * i);
    for ( j = 0; j < *((unsigned __int16 *)v27 + 21); ++j )
    {
      v25 = v27[5] + 8 * j;
      v10 = v31;
      v31 = rf_collision_static_triangle_dispatch_radius(v29, v27, j, (int)rhs, (int)a4, *(_WORD *)(v25 + 6) & 0x20)
          | v10;
      if ( v31 && (*((_DWORD *)rhs + 19) & 1) != 0 )
      {
        v11 = rf_model_mesh144_get_lod_table_translation(v34, v16);
        rf_vector_accumulate((float *)a4 + 1, v11);
        return 1;
      }
    }
  }
  if ( v31 )
  {
    v12 = rf_model_mesh144_get_lod_table_translation(v34, v15);
    rf_vector_accumulate((float *)a4 + 1, v12);
  }
  return v31;
}

