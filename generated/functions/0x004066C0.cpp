// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004066C0 rf_ai_mode9_face_and_fire_auxiliary_target
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI movement-state/route/association/reaction chains, independently reviewed native branches and original
// float/dispatch constants and native signed/x87/stack/callback ABI): One required AI block, central mode9 handler. Resolves COMMON auxiliary handle+728; missing exits untouched.
// Calls410920(owner,target COMMON+60), discardsST0. Signed DWORD route count at block+744>0 calls route-update(route,extra0), ignoring result before remaining aiming work. Current
// descriptor/speed predicate437E80(owner)==EXACT1 projects target COMMON position to owner COMMON Y+64 before subtraction; every other AL uses full three-dimensional
// target-minus-owner COMMON positions. Normalizes direction without own zero/finite guard, dot with owner COMMON forward row+96, stores float32. Ordered strictly>DOUBLE0.95
// calls431FD0 with exactly six slots(owner,0,0,0,0,0), then433A90(owner,0) without checking first return. Equality/NaN reject. No target entity-type, selected weapon, reload or
// authority admission here; delegates own further policy.
void __cdecl rf_ai_mode9_face_and_fire_auxiliary_target(int *a1)
{
  float *v1; // eax
  float *v2; // eax
  float v3[3]; // [esp+0h] [ebp-50h] BYREF
  float v4[3]; // [esp+Ch] [ebp-44h] BYREF
  float copy_result[3]; // [esp+18h] [ebp-38h] BYREF
  float out_vector[3]; // [esp+24h] [ebp-2Ch] BYREF
  float lhs[3]; // [esp+30h] [ebp-20h] BYREF
  float destination[3]; // [esp+3Ch] [ebp-14h] BYREF
  int v9; // [esp+48h] [ebp-8h]
  float v10; // [esp+4Ch] [ebp-4h]

  v9 = rf_object_resolve_handle(a1[182]);
  if ( v9 )
  {
    sub_410920(*a1, (const float *)(v9 + 60));
    if ( a1[186] > 0 )
      rf_ai_route_update((int)(a1 + 186));
    rf_vector3_default_construct_noop(destination);
    if ( sub_437E80(*a1) )
    {
      rf_vector3_copy_return_destination(lhs, (float *)(v9 + 60));
      lhs[1] = *(float *)(*a1 + 64);
      v1 = rf_vector_subtract(lhs, out_vector, (const float *)(*a1 + 60));
      rf_vector_copy(destination, copy_result, v1);
    }
    else
    {
      v2 = rf_vector_subtract((const float *)(v9 + 60), v4, (const float *)(*a1 + 60));
      rf_vector_copy(destination, v3, v2);
    }
    rf_vector_normalize_reciprocal_sqrt(destination);
    v10 = rf_vector_dot((float *)(*a1 + 96), destination);
    if ( v10 > 0.95 )
    {
      sub_431FD0(*a1, 0, 0, nullptr, 0, 0);
      rf_entity_fire_secondary_or_begin_charge((_DWORD *)*a1, 0);
    }
  }
}

