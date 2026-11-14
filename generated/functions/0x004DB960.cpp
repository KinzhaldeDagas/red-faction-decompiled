// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004DB960 rf_object_segment_model_hit_fraction
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, player runtime timers/projectiles, special-use jump table, collision list order, native matrix aliases and console command state): Cdecl object,start,end,output fraction. Requires object flags124 mask0x10, model128 nonNULL, object !=GLOBAL current entity681E38 (not arbitrary caller entity). Segment-AABB admission uses object400/412. Builds query descriptor at EBP-68h: object position+0,orientation+12,start+48,direction(end-start)+60,min scalar+72=0,DWORD+76=1; constructor only constructs vector/matrix members. Calls model collide-all adapter(model,&query,&result,1); any nonzero return copies result first float to output and returnsAL1. Failure returns0 without output write. No inactive/dead filter here, own object NULL check, fraction bounds/minimization or incoming output threshold read.
char __cdecl rf_object_segment_model_hit_fraction(int a1, float *rhs, float *lhs, float *a4)
{
  float *v5; // eax
  float v6[3]; // [esp+0h] [ebp-C4h] BYREF
  float v7[3]; // [esp+Ch] [ebp-B8h] BYREF
  float out_vector[3]; // [esp+18h] [ebp-ACh] BYREF
  float copy_result[3]; // [esp+24h] [ebp-A0h] BYREF
  float v10[8]; // [esp+30h] [ebp-94h] BYREF
  float v11[3]; // [esp+50h] [ebp-74h] BYREF
  float v12[3]; // [esp+5Ch] [ebp-68h] BYREF
  float v13[9]; // [esp+68h] [ebp-5Ch] BYREF
  float destination[3]; // [esp+8Ch] [ebp-38h] BYREF
  float v15[11]; // [esp+98h] [ebp-2Ch] BYREF

  if ( (*(_DWORD *)(a1 + 124) & 0x10) == 0 )
    return 0;
  if ( !*(_DWORD *)(a1 + 128) || a1 == dword_681E38 )
    return 0;
  rf_vector3_default_construct_noop(v11);
  if ( !rf_segment_intersects_aabb((float *)(a1 + 400), (float *)(a1 + 412), rhs, lhs, v11) )
    return 0;
  rf_model_collision_query_construct_noop((char *)v12);
  rf_model_collision_result_construct_noop((int)v10);
  rf_vector_copy(destination, copy_result, rhs);
  v5 = rf_vector_subtract(lhs, out_vector, rhs);
  rf_vector_copy(v15, v7, v5);
  LODWORD(v15[4]) = 1;
  v15[3] = 0.0;
  rf_matrix3_copy(v13, (const float *)(a1 + 72));
  rf_vector_copy(v12, v6, (const float *)(a1 + 60));
  if ( !rf_model_handle_collide_all_adapter(*(_DWORD **)(a1 + 128), (int)v12, (int)v10, 1) )
    return 0;
  *a4 = v10[0];
  return 1;
}

