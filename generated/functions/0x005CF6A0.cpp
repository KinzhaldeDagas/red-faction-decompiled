// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CF6A0 rf_v3c_asset_collide_skinned_meshes
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, static/skinned V3C mesh callers, collision branch comparisons and primitive helpers): Gets selected geometry through asset.selectedMesh+144->LODtable+140->selected slot. Computes broadphase endpoint ONCE as workingStart+workingDelta*incoming hitFraction. Builds character skin transforms,then for each56-byte batch skins each vertex into global scratch1DC0BB0. Up to4 unsigned-byte weights,stops at first zero;bone byte index selects instance palette+2400+48*bone,affine-transforms source point and accumulates weight/256 WITHOUT renormalization. Zero first weight yields zero point. Bounds start min=FLT_MAX,max=positive FLT_MIN;helper5B1310 uses min/ELSE-max update,so repeated descending points can leave max below min or omit actual maximum. Example vertices3,2,1 on an axis leave min1/maxFLT_MIN;not a robust extrema
// initializer. Expands bounds by radius and tests capped segment. Iterates signed16 triangle indices into global skinned scratch,tests triangles5CFAC0 with tag0;query flag1 returns first hit. No vertex/bone/scratch capacity,index,LOD or weight sum checks. Global scratch makes concurrent/reentrant use unsafe absent external synchronization;normal/point remain working coordinates.
char __cdecl rf_v3c_asset_collide_skinned_meshes(void *a1, void *a2, void *a3, void *a4)
{
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  char v7; // bl
  float scalar; // [esp+10h] [ebp-D4h]
  float v10[3]; // [esp+18h] [ebp-CCh] BYREF
  float v11[3]; // [esp+24h] [ebp-C0h] BYREF
  float copy_result[3]; // [esp+30h] [ebp-B4h] BYREF
  float v13[3]; // [esp+3Ch] [ebp-A8h] BYREF
  float scaled_result[3]; // [esp+48h] [ebp-9Ch] BYREF
  float *v15; // [esp+54h] [ebp-90h]
  float *v16; // [esp+58h] [ebp-8Ch]
  __int16 *v17; // [esp+5Ch] [ebp-88h]
  float *v18; // [esp+60h] [ebp-84h]
  int m; // [esp+64h] [ebp-80h]
  int k; // [esp+68h] [ebp-7Ch]
  float v21[3]; // [esp+6Ch] [ebp-78h] BYREF
  float source[3]; // [esp+78h] [ebp-6Ch] BYREF
  int j; // [esp+84h] [ebp-60h]
  _BYTE v24[12]; // [esp+88h] [ebp-5Ch] BYREF
  float destination[3]; // [esp+94h] [ebp-50h] BYREF
  float *v26; // [esp+A0h] [ebp-44h]
  int v27; // [esp+A4h] [ebp-40h]
  float v28[3]; // [esp+A8h] [ebp-3Ch] BYREF
  float v29[3]; // [esp+B4h] [ebp-30h] BYREF
  int v30; // [esp+C0h] [ebp-24h]
  int i; // [esp+C4h] [ebp-20h]
  char v32; // [esp+CBh] [ebp-19h]
  float v33[3]; // [esp+CCh] [ebp-18h] BYREF
  float sum_result[3]; // [esp+D8h] [ebp-Ch] BYREF

  v32 = 0;
  rf_vector3_default_construct_noop(v33);
  rf_vector3_default_construct_noop(v28);
  rf_vector3_default_construct_noop(v29);
  v4 = rf_vector_multiply_scalar((const float *)a3 + 23, scaled_result, *(float *)a4);
  rf_vector_add((const float *)a3 + 20, sum_result, v4);
  v30 = *(_DWORD *)(*(_DWORD *)(*((_DWORD *)a1 + 36) + 140) + 4 * **(_DWORD **)(*((_DWORD *)a1 + 36) + 140));
  rf_character_build_skin_transforms((int)a2, 0, (int)a1, 0, 0, 0, 1);
  for ( i = 0; i < *(unsigned __int16 *)(v30 + 12); ++i )
  {
    rf_vector3_set_components_thiscall(v28, 3.4028235e38, 3.4028235e38, 3.4028235e38);
    rf_vector3_set_components_thiscall(v29, 1.1754944e-38, 1.1754944e-38, 1.1754944e-38);
    v26 = *(float **)(*(_DWORD *)(v30 + 8) + 56 * i + 4);
    v27 = *(_DWORD *)(*(_DWORD *)(v30 + 8) + 56 * i + 28);
    rf_vector3_default_construct_noop(destination);
    rf_vector3_default_construct_noop(v24);
    for ( j = 0; j < *(unsigned __int16 *)(*(_DWORD *)(v30 + 8) + 56 * i + 40); ++j )
    {
      rf_vector3_default_construct_noop(v21);
      v21[0] = *v26++;
      v21[1] = *v26++;
      v21[2] = *v26++;
      rf_vector3_set_components_return_destination(source, 0.0, 0.0, 0.0);
      for ( k = 0; k < 4 && *(_BYTE *)(v27 + 8 * j + k); ++k )
      {
        v5 = rf_affine3x4_transform_point((float *)a2 + 12 * *(unsigned __int8 *)(v27 + 8 * j + k + 4) + 600, v13, v21);
        rf_vector_copy(destination, copy_result, v5);
        scalar = (double)*(unsigned __int8 *)(v27 + 8 * j + k) / 256.0;
        v6 = rf_vector_multiply_scalar(destination, v11, scalar);
        rf_vector_accumulate(source, v6);
      }
      rf_vector_copy(&flt_1DC0BB0[3 * j], v10, source);
      rf_aabb_include_point_min_else_max(v28, v29, source);
    }
    rf_vector3_subtract_scalar_in_place(v28, *((float *)a3 + 18));
    rf_vector3_add_scalar_in_place(v29, *((float *)a3 + 18));
    if ( rf_segment_intersects_aabb(v28, v29, (float *)a3 + 20, sum_result, v33) )
    {
      for ( m = 0; m < *(unsigned __int16 *)(*(_DWORD *)(v30 + 8) + 56 * i + 42); ++m )
      {
        v17 = (__int16 *)(*(_DWORD *)(*(_DWORD *)(v30 + 8) + 56 * i + 20) + 8 * m);
        v15 = &flt_1DC0BB0[3 * *v17];
        v18 = &flt_1DC0BB0[3 * v17[1]];
        v16 = &flt_1DC0BB0[3 * v17[2]];
        v7 = v32;
        v32 = rf_collision_test_skinned_triangle(0, v15, v18, v16, a3, a4, sum_result) | v7;
        if ( v32 && (*((_DWORD *)a3 + 19) & 1) != 0 )
          return 1;
      }
    }
  }
  return v32;
}

