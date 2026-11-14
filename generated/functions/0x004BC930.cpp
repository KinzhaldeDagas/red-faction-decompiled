// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC930 rf_object_reactivate_from_respawn
// UNREALRED VERIFIED [mission-protection-20261020] UnHide pending-show reuses this in-place common reactivation: clears0x4000, resumes entity emitters/voice, refreshes idle deadline, recursively reactivates held clutter and restores physics handling. It does not allocate a replacement object.
// UNREALRED VERIFIED [mission-visibility-20261020] Reactivation clears common-inactive mask0x4000 in place, enables child emitter bytes, sets ambient source gain1, refreshes idle deadline and recursively reactivates held clutter. The physics-owner branch and common0x8000 cleanup are additional behavior. Repeated reactivation calls still run these side effects; do not optimize solely on a visible-state transition.
// UNREALRED VERIFIED [mission-unhide-20261020] Repeated reactivation still performs entity idle-deadline refresh437370. UnrealRed composes common inactivity with explicit world pause and ordinary death visibility/collision intent, so reactivation does not resume a still-paused actor or resurrect dead locomotion. Missing source emitter/ambient/held-clutter owners remain parity gaps.
void __cdecl rf_object_reactivate_from_respawn(_DWORD *a1)
{
  _BYTE **v1; // eax
  int j; // [esp+4h] [ebp-14h]
  int i; // [esp+8h] [ebp-10h]
  int k; // [esp+Ch] [ebp-Ch]
  _DWORD *v5; // [esp+10h] [ebp-8h]
  _DWORD *v6; // [esp+14h] [ebp-4h]

  if ( a1 )
  {
    a1[31] &= ~0x4000u;
    v6 = (_DWORD *)rf_entity_resolve_handle(a1[11]);
    if ( v6 )
    {
      for ( i = v6[154]; i; i = *(_DWORD *)(i + 336) )
        *(_BYTE *)(i + 320) = 1;
      for ( j = 0; j < rf_receiver_get_first_dword(v6 + 1286); ++j )
      {
        v1 = (_BYTE **)sub_552200(v6 + 1286, j);
        rf_emitter_enable(*v1);
      }
      if ( v6[513] != -1 )
        rf_ambient_voice_set_source_gain(v6[513], 1.0);
      rf_entity_refresh_idle_animation_deadline((int)v6);
      for ( k = 0; k < 2; ++k )
      {
        v5 = (_DWORD *)rf_clutter_find_by_uid(v6[k + 1303]);
        if ( v5 )
          rf_object_reactivate_from_respawn(v5);
      }
    }
    if ( a1[32] && rf_model_descriptor_get_kind(a1[32]) == 3 )
      rf_model_handle_set_cyclic_mix_adapter((int *)a1[32], 0, 1.0);
    if ( (a1[31] & 0x8000) != 0 )
    {
      rf_collision_register_object_against_active_list((int)a1);
      a1[31] &= ~0x8000u;
    }
  }
}

