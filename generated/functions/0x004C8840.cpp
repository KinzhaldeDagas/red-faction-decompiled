// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C8840 rf_glass_shard_launch_directional_delayed
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, full rectangular/general quad tessellation, ordered edge selection and stale loop indices, native UV/grid coordinates, pool freshness and delayed launch semantics): 
// Cdecl(shard,impactPosition,direction). FIRST samples min-dotF32.9700000286102295 cone into velocity64 from supplied direction (no own normalization). Computes F32Euclidean distance
// from impact to shard center. Only ordered distance<DOUBLE0.10000000149011612 clamps toF32.1; NaN staysNaN. Computes/stores F32reciprocal squared distance but never uses it for
// speed/delay. Only ordered distance<.5 selects near: reset delay108,velocity*=random[1,8],arm112=500ms.
// Distance>=.5 OR unordered takes far: signed delay=trunc(distance*200) + trunc(random[100,500]) via separate __ftol2_sse calls and unchecked32bit addition. Arms108(delay),multiplies
// velocity components by0 (not unconditional raw zeros for NaN/inf),resets112. No hidden stored launch velocity: updater5EE0 at expiry only clears108/arms112, does not restore cone
// velocity, so finite far shards resume gravity falling from zero velocity. Does not set budget/flags/attachment/spin/room; return timer delegate artifact, not success.
_DWORD *__cdecl rf_glass_shard_launch_directional_delayed(int a1, float *a2, float *a3)
{
  int v4; // esi
  int v5; // eax
  float v6[3]; // [esp-8h] [ebp-20h] BYREF
  float v7; // [esp+4h] [ebp-14h]
  float v8; // [esp+10h] [ebp-8h]
  float v9; // [esp+14h] [ebp-4h]

  v7 = 0.97000003;
  rf_vector3_copy_return_destination(v6, a3);
  rf_random_unit_vector_in_cone((float *)(a1 + 64), v6[0], v6[1], v6[2], v7);
  v8 = rf_vector_distance(a2, (const float *)(a1 + 8));
  if ( v8 < 0.1000000014901161 )
    v8 = 0.1;
  v9 = 1.0 / (v8 * v8);
  if ( v8 >= 0.5 )
  {
    v4 = (int)(v8 * 200.0);
    v5 = (int)rf_random_float_range(100.0, 500.0);
    rf_replicator_arm_milliseconds((int *)(a1 + 108), v5 + v4);
    rf_vector3_scale_in_place_return_self((float *)(a1 + 64), 0.0);
    return rf_replicator_reset((_DWORD *)(a1 + 112));
  }
  else
  {
    rf_replicator_reset((_DWORD *)(a1 + 108));
    v7 = rf_random_float_range(1.0, 8.0);
    rf_vector3_scale_in_place_return_self((float *)(a1 + 64), v7);
    return (_DWORD *)rf_replicator_arm_milliseconds((int *)(a1 + 112), 500);
  }
}

