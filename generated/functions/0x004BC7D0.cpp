// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BC7D0 rf_object_mark_hidden_inactive
// UNREALRED VERIFIED [mission-protection-20261020] UnHide pending-hide targets common inactive bit0x4000 and entity emitter/voice/action/held-clutter cleanup. A plain Unreal mesh visibility toggle does not reproduce this lifecycle. The opposite pending-show calls0x4BC930.
// UNREALRED VERIFIED [mission-visibility-20261020] Side-effect refinement: call0x422A40 receives entity UID and equipped weapon index(+676); it stops weapon firing, clears the per-weapon firing byte and entity flag0x2000, stops relevant loop voices and ends flame effects. It is not a generic AI-route cancellation call. Hide also disables child emitter bytes, sets ambient voice gain0, recursively hides both held clutter UIDs, and tears down attached effect+5080.
// UNREALRED VERIFIED [mission-unhide-20261020] Common inactive flag0x4000 is shared with item collection/respawn. UnrealRed item mission changes and native collection/respawn synchronize the same retained inactivity override; the independent mover pickup receipt gate is not overwritten. Entity hiding stops weapon firing while preserving logical common identity.
void __cdecl rf_object_mark_hidden_inactive(int a1)
{
  _BYTE **v1; // eax
  int j; // [esp+4h] [ebp-14h]
  int i; // [esp+8h] [ebp-10h]
  int k; // [esp+Ch] [ebp-Ch]
  int v5; // [esp+10h] [ebp-8h]
  int v6; // [esp+14h] [ebp-4h]

  if ( a1 )
  {
    *(_DWORD *)(a1 + 124) |= 0x4000u;
    v6 = rf_entity_resolve_handle(*(_DWORD *)(a1 + 44));
    if ( v6 )
    {
      for ( i = *(_DWORD *)(v6 + 616); i; i = *(_DWORD *)(i + 336) )
        *(_BYTE *)(i + 320) = 0;
      for ( j = 0; j < rf_receiver_get_first_dword((void *)(v6 + 5144)); ++j )
      {
        v1 = (_BYTE **)sub_552200((_DWORD *)(v6 + 5144), j);
        rf_emitter_disable(*v1);
      }
      if ( *(_DWORD *)(v6 + 2052) != -1 )
        rf_ambient_voice_set_source_gain(*(_DWORD *)(v6 + 2052), 0.0);
      for ( k = 0; k < 2; ++k )
      {
        v5 = rf_clutter_find_by_uid(*(_DWORD *)(v6 + 4 * k + 5212));
        if ( v5 )
          rf_object_mark_hidden_inactive(v5);
      }
      rf_entity_stop_weapon_firing(*(_DWORD *)(v6 + 44), *(_DWORD *)(v6 + 676));
      if ( *(_DWORD *)(v6 + 5080) )
      {
        rf_burn_effect_release_record(*(float **)(v6 + 5080), 0);
        *(_DWORD *)(v6 + 5080) = 0;
      }
    }
  }
}

