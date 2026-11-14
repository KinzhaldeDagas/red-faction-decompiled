// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C73B0 rf_glass_shard_launch_radial
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl(shard,impactPosition,lowBYTEfastMode). Resets delay108,arms companion deadline112=500ms. Direction=normalize(shard.center8-impactPosition) via unitX zero/NaN fallback, then
// random min-dotF32.9700000286102295 cone. Nonzero BYTE ->velocity64=direction*10,zero->*4, binary32 vector stores. Returns vector-copy result. Does NOT set budget96, clear
// attachment100 or flags196, randomize spin, alter room/bucket, change position or create/delete nodes. Far-mode timer behavior belongs8840; this always launches immediately.
float *__cdecl rf_glass_shard_launch_radial(int a1, float *rhs, char a3)
{
  float *v3; // eax
  float *v5; // eax
  float v6[3]; // [esp-Ch] [ebp-50h] BYREF
  float scalar; // [esp+0h] [ebp-44h]
  float v8[3]; // [esp+4h] [ebp-40h] BYREF
  float v9[3]; // [esp+10h] [ebp-34h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-28h] BYREF
  float scaled_result[4]; // [esp+28h] [ebp-1Ch] BYREF
  float out_vector[3]; // [esp+38h] [ebp-Ch] BYREF

  rf_replicator_reset((_DWORD *)(a1 + 108));
  rf_replicator_arm_milliseconds((int *)(a1 + 112), 500);
  rf_vector_subtract((const float *)(a1 + 8), out_vector, rhs);
  rf_vector_normalize(out_vector);
  scalar = 0.97000003;
  rf_vector3_copy_return_destination(v6, out_vector);
  rf_random_unit_vector_in_cone(out_vector, v6[0], v6[1], v6[2], scalar);
  if ( a3 )
  {
    v3 = rf_vector_multiply_scalar(out_vector, scaled_result, 10.0);
    return rf_vector_copy((float *)(a1 + 64), copy_result, v3);
  }
  else
  {
    v5 = rf_vector_multiply_scalar(out_vector, v9, 4.0);
    return rf_vector_copy((float *)(a1 + 64), v8, v5);
  }
}

