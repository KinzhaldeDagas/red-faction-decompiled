// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040B1A0 sub_40B1A0
// UNREALRED VERIFIED [combat-panic-20261104]: Enter numeric17: attached-use-turret detach first; truncate double(binary32 duration)*1000; extend AI+0x254 only if signedRemaining55F0B0<durationMs. This extension precedes a3/currentMode17 short-circuit. For a3=0 already17, do not repeat cleanup/drop/route. Otherwise scripted context clear, Entity+810 mask~02000000,+834=-1,idle deadline refresh,stop selected firing,439220 selected-item drop(a2=0),4355A0 presentation,mode17,secondary1,40EAB0 random local route. Native bool/return after route failure does not undo committed entry.
char __cdecl sub_40B1A0(int *a1, float a2, char a3)
{
  char result; // al
  int v4; // [esp+0h] [ebp-4h]

  if ( rf_entity_has_attached_use_turret(*a1) )
    sub_40C340(a1);
  v4 = (int)(a2 * 1000.0);
  if ( rf_replicator_signed_remaining_milliseconds(a1 + 149) < v4 )
    rf_replicator_arm_milliseconds(a1 + 149, v4);
  if ( a3 || (result = (char)a1, a1[160] != 17) )
  {
    rf_ai_clear_scripted_animation_context(a1);
    *(_DWORD *)(*a1 + 2064) &= ~0x2000000u;
    *(_DWORD *)(*a1 + 2100) = -1;
    rf_entity_refresh_idle_animation_deadline(*a1);
    rf_entity_stop_weapon_firing(*(_DWORD *)(*a1 + 44), a1[1]);
    rf_character_drop_selected_weapon_item(*a1, 0);
    sub_4355A0(*a1);
    rf_ai_numeric_mode_write(a1, 17, -1, -1);
    rf_ai_secondary_state_write((int)a1, 1);
    return sub_40EAB0(*(_DWORD *)(*a1 + 44));
  }
  return result;
}

