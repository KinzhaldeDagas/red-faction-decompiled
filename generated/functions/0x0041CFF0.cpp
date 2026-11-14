// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041CFF0 rf_corpse_update_drop_transition
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Thiscall corpse, no stack args. Computes dot(velocity+324,contactNormal+448). ONLY ordered dot<-20 takes hard-impact path: resolves contact UID+484 as projectile type2; class+612 mask0x20 suppresses blood decal, otherwise calls0x43DCD0(100,position+228,velocity+324), THREE DWORD arguments. Always plays positional event34 and marks deferred deletion, returns0. Ordered dot>=-20 OR unordered takes contact/drop path. Corpse flags+668 mask0x20 clear simply deactivates physics and returns0. With mask0x20 set, model kind2 and drop action+700!=-1 reset cyclic/actions, start held action, advance by0.75*authored duration, and if voice+724 not playing store positional event33 voice.
// Then support helper0x41CDC0 result0 deactivates physics and zeros velocity+324/+336. Only ordered reciprocal/contact float+468==0 plus resolvable UID+484 requests retirement; NaN skips. Returns1 on entire mask0x20 path, even if not settled. No one-shot action flag reset or immediate free; repeated calls may restart held drop action.
int __thiscall rf_corpse_update_drop_transition(int this)
{
  float v2; // [esp+14h] [ebp-18h]
  float v4; // [esp+1Ch] [ebp-10h]
  int v5; // [esp+20h] [ebp-Ch]
  bool v6; // [esp+27h] [ebp-5h]
  float v7; // [esp+28h] [ebp-4h]

  v7 = rf_vector_dot((float *)(this + 324), (float *)(this + 448));
  if ( v7 >= -20.0 )
  {
    if ( (*(_DWORD *)(this + 668) & 0x20) != 0 )
    {
      if ( rf_model_descriptor_get_kind(*(_DWORD *)(this + 128)) == 2 && *(_DWORD *)(this + 700) != -1 )
      {
        rf_model_handle_reset_cyclic_adapter(*(_DWORD *)(this + 128));
        rf_model_handle_reset_actions_adapter(*(_DWORD *)(this + 128));
        rf_vfx_start_instance(*(int **)(this + 128), *(_DWORD *)(this + 700), 1.0, 1);
        v4 = rf_model_animation_duration_seconds((unsigned int *)*(_DWORD *)(this + 128), *(_DWORD *)(this + 700));
        v2 = v4 * 0.75;
        rf_vfx_update_instance(*(int **)(this + 128), v2, 0, 0, 0, 1);
        if ( !rf_gamesound_voice_is_playing(*(_DWORD *)(this + 724)) )
          *(_DWORD *)(this + 724) = rf_gamesound_play_positional_event(
                                      33,
                                      (float *)(this + 228),
                                      1.0,
                                      (int)&unk_17F10B0,
                                      0);
      }
      if ( !rf_corpse_probe_support_and_adjust_contact_velocity(this) )
      {
        rf_physics_state_deactivate(this + 136);
        rf_vector3_zero_return_destination((float *)(this + 324));
        rf_vector3_zero_return_destination((float *)(this + 336));
        if ( *(float *)(this + 468) == 0.0 )
        {
          if ( rf_object_resolve_handle(*(_DWORD *)(this + 484)) )
            rf_corpse_schedule_eviction(this);
        }
      }
      return 1;
    }
    else
    {
      rf_physics_state_deactivate(this + 136);
      return 0;
    }
  }
  else
  {
    v6 = 1;
    v5 = rf_projectile_resolve_uid_type2(*(_DWORD *)(this + 484));
    if ( v5 )
      v6 = (*(_DWORD *)(*(_DWORD *)(v5 + 660) + 612) & 0x20) == 0;
    if ( v6 )
      rf_blood_decal_trace_and_submit(100.0, (const float *)(this + 228), (const float *)(this + 324));
    rf_gamesound_play_positional_event(34, (float *)(this + 228), 1.0, (int)&unk_17F10B0, 0);
    rf_object_mark_for_deferred_delete(this);
    return 0;
  }
}

