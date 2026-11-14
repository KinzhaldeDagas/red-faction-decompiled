// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DB630 rf_player_adjust_projectile_spawn_for_nearby_surfaces
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl player,output position. Missing resolved entity leaves output untouched. Uses entity view position2004 and full matrix2016; decompiler vector is initialized third row of nine-float matrix, not separate uninitialized data. Tests segment start=view position,end=start+2*forward against first eligible model in clutter/entity/corpse list order. Model hit writes output=start+(end-start)*float(modelFraction*double0.8999999761581421). Then geometry query flags0 with result descriptor; only AL EXACT1 accepted. Geometry overrides model hit only when ORDERED modelFraction>worldFraction; equality/unordered retains model result. Without model hit, any accepted world result is used regardless of
// fraction validity. If neither accepted hit, output=start+forward (one unit along raw forward row, without normalization). No global nearest-model search, fraction clamp, actor-specific self exclusion or own pointer checks.
void __cdecl rf_player_adjust_projectile_spawn_for_nearby_surfaces(int a1, float *destination)
{
  float *v2; // eax
  float *v3; // eax
  float *v4; // eax
  float *v5; // eax
  float *v6; // eax
  float *v7; // eax
  float *v8; // eax
  float *v9; // eax
  float v10; // [esp+4h] [ebp-11Ch]
  float scalar; // [esp+8h] [ebp-118h]
  float v12[3]; // [esp+Ch] [ebp-114h] BYREF
  float v13[3]; // [esp+18h] [ebp-108h] BYREF
  float v14[3]; // [esp+24h] [ebp-FCh] BYREF
  float v15[3]; // [esp+30h] [ebp-F0h] BYREF
  float v16[3]; // [esp+3Ch] [ebp-E4h] BYREF
  float v17[3]; // [esp+48h] [ebp-D8h] BYREF
  float copy_result[3]; // [esp+54h] [ebp-CCh] BYREF
  float sum_result[3]; // [esp+60h] [ebp-C0h] BYREF
  float v20[3]; // [esp+6Ch] [ebp-B4h] BYREF
  float out_vector[3]; // [esp+78h] [ebp-A8h] BYREF
  float scaled_result[3]; // [esp+84h] [ebp-9Ch] BYREF
  char v23; // [esp+92h] [ebp-8Eh]
  char v24; // [esp+93h] [ebp-8Dh]
  int v25; // [esp+94h] [ebp-8Ch]
  float lhs[3]; // [esp+98h] [ebp-88h] BYREF
  float v27; // [esp+A4h] [ebp-7Ch] BYREF
  float rhs[3]; // [esp+A8h] [ebp-78h] BYREF
  _BYTE v29[24]; // [esp+B4h] [ebp-6Ch] BYREF
  float vector[3]; // [esp+CCh] [ebp-54h] BYREF
  float v31[6]; // [esp+D8h] [ebp-48h] BYREF
  float v32; // [esp+F0h] [ebp-30h]

  v25 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 20));
  if ( v25 )
  {
    rf_vector3_copy_return_destination(rhs, (float *)(v25 + 2004));
    rf_matrix3_copy_construct((int)v29, (const void *)(v25 + 2016));
    v2 = rf_vector_multiply_scalar(vector, scaled_result, 2.0);
    rf_vector_add(rhs, lhs, v2);
    v27 = 0.0;
    v24 = 0;
    v23 = 0;
    if ( rf_segment_find_first_collidable_model_fraction((int)rhs, (int)lhs, &v27) )
    {
      scalar = v27 * 0.8999999761581421;
      v3 = rf_vector_subtract(lhs, out_vector, rhs);
      v4 = rf_vector_multiply_scalar(v3, v20, scalar);
      v5 = rf_vector_add(rhs, sum_result, v4);
      rf_vector_copy(destination, copy_result, v5);
      v24 = 1;
    }
    rf_physics_hit_record_construct_noop((char *)v31);
    if ( rf_geometry_segment_is_obstructed(rhs, lhs, 0, v31) == 1 && (!v24 || v27 > (double)v32) )
    {
      v10 = v32 * 0.8999999761581421;
      v6 = rf_vector_subtract(lhs, v17, rhs);
      v7 = rf_vector_multiply_scalar(v6, v16, v10);
      v8 = rf_vector_add(rhs, v15, v7);
      rf_vector_copy(destination, v14, v8);
      v23 = 1;
    }
    if ( !v24 && !v23 )
    {
      v9 = rf_vector_add(rhs, v13, vector);
      rf_vector_copy(destination, v12, v9);
    }
  }
}

