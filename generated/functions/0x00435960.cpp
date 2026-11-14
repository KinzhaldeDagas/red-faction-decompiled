// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00435960 rf_entity_vertical_sweep_copy_hit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity body-action/movement/stance/holster controls, collision queries, LOD pointer/float-return ABI and
// native partial-state flows and native signed/x87/stack/callback ABI): Cdecl(outHit40,required entity,FLOAT distance), canonicalAL0/1. Builds local sweep query: constructor clears
// face-hint DWORD0 only; auxiliary vector+4=zero, matrix+16=identity; start vector+52=entity COMMON60; displacement+64=(0,-distance,0) by x87FCHS/float stores; radiusFLOAT+76=entity
// FLOAT384; flagsDWORD+80=0. Local result constructor is no-op. Call52F8D0 with ECX=world6FC420 and stack(query,result,raw1), ignore its return. Report DWORD0 ANY NONZERO, including
// negative, invokes43CA30(this=caller outHit,source=local result) and explicitAL1. Exactly0 returnsAL0 leaving caller hit record unchanged. No signedpositive test, output
// initialization on failure, pointer/room/shape/dead/authority or nonnegative/finite/radius validation. Negative distance sweeps upward rather than being clamped; query and result
// side effects are not rolled back.
char __cdecl rf_entity_vertical_sweep_copy_hit(void *out_hit, int entity, float distance)
{
  float v4; // [esp+4h] [ebp-ACh]
  float copy_result[3]; // [esp+Ch] [ebp-A4h] BYREF
  float v6[10]; // [esp+18h] [ebp-98h] BYREF
  char v7[4]; // [esp+40h] [ebp-70h] BYREF
  float v8[3]; // [esp+44h] [ebp-6Ch] BYREF
  float v9[9]; // [esp+50h] [ebp-60h] BYREF
  float destination[3]; // [esp+74h] [ebp-3Ch] BYREF
  float v11[12]; // [esp+80h] [ebp-30h] BYREF

  rf_solid_collision_query_construct_clear_face_hint(v7);
  rf_solid_collision_result_construct_noop((int)v6);
  rf_vector_copy(destination, copy_result, (const float *)(entity + 60));
  v4 = -distance;
  rf_vector3_set_components_thiscall(v11, 0.0, v4, 0.0);
  v11[3] = *(float *)(entity + 384);
  v11[4] = 0.0;
  rf_vector3_zero_return_destination(v8);
  rf_identity_orientation_matrix(v9);
  rf_world_collision_sweep((char *)rf_world_solid, (int)v7, (int)v6, 1);
  if ( !LODWORD(v6[0]) )
    return 0;
  rf_collision_hit40_assign((float *)out_hit, v6);
  return 1;
}

