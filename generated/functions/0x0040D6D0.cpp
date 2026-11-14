// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040D6D0 rf_ai_transfer_budget_to_retained_entity_health
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required AI block); no uniform AL/EAX result. Resolves retained full handle block+704 as ENTITY and captures pointer. Miss
// delegates saved-state restore40A2A0(block) and exits. Fast distance(owner COMMON position+60,target+60) is rounded float32; compares against unrounded x87 sum owner FLOAT+120 +
// target FLOAT+120 + DOUBLE3.5. Only ORDERED distance>sum resets owner model actions via565020(owner+128 model handle), restores saved state and exits; equality/less/UNORDERED
// proceeds. Constructs local vector without initializing, copies target point via4BCCB0(target,&point), then calls410920(owner,&point) and discards its ST0 result. Computes float32
// deficit=target class(+660) FLOAT+68 minus target FLOAT health+52. ORDERED deficit<=0 calls40A2A0 but DOES NOT RETURN: captured target and deficit remain in use afterwards, even if
// restoration changes block state. Independently tests block+1220 elapsed deadline; AL0 exits, ANY nonzero continues, without arming/resetting deadline here. Transfer starts at
// deficit; if ORDERED current FLOAT budget block+1216<=deficit replaces transfer with budget, otherwise—including UNORDERED—retains deficit. No nonnegative/finite clamp is applied to
// budget or transfer. Stores float32 budget=budget-transfer, then float32 target health=health+transfer, then clamps target health in place to lower0 and freshly re-read class
// FLOAT+68 through40D620. Its ordered lower/upper comparisons leave NaN health unchanged and do not normalize inverted bounds. Finally restores saved state again. Thus nonpositive
// deficits can still transfer, NaNs can propagate and an earlier restoration does not suppress elapsed transfer; stores/delegate effects are not rolled back. No target resolution or
// range check is repeated after the first restoration.
void __cdecl rf_ai_transfer_budget_to_retained_entity_health(int *a1)
{
  float target_point[3]; // [esp+8h] [ebp-18h] BYREF
  float v2; // [esp+14h] [ebp-Ch]
  float v3; // [esp+18h] [ebp-8h]
  int v4; // [esp+1Ch] [ebp-4h]

  v4 = rf_entity_resolve_handle(a1[176]);
  if ( v4 )
  {
    v2 = rf_vector_fast_distance((const float *)(*a1 + 60), (const float *)(v4 + 60));
    if ( v2 <= *(float *)(*a1 + 120) + *(float *)(v4 + 120) + 3.5 )
    {
      rf_vector3_default_construct_noop(target_point);
      rf_object_copy_entity_vector7D4_or_position(v4, target_point);
      sub_410920(*a1, target_point);
      v3 = *(float *)(*(_DWORD *)(v4 + 660) + 68) - *(float *)(v4 + 52);
      if ( v3 <= 0.0 )
        sub_40A2A0(a1);
      if ( rf_replicator_has_elapsed(a1 + 305) )
      {
        if ( *((float *)a1 + 304) <= (double)v3 )
          v3 = *((float *)a1 + 304);
        *((float *)a1 + 304) = *((float *)a1 + 304) - v3;
        *(float *)(v4 + 52) = *(float *)(v4 + 52) + v3;
        rf_float_clamp_in_place((float *)(v4 + 52), 0.0, *(float *)(*(_DWORD *)(v4 + 660) + 68));
        sub_40A2A0(a1);
      }
    }
    else
    {
      rf_model_handle_reset_actions_adapter(*(_DWORD *)(*a1 + 128));
      sub_40A2A0(a1);
    }
  }
  else
  {
    sub_40A2A0(a1);
  }
}

