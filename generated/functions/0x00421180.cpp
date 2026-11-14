// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00421180 rf_entity_weapon_update
// UNREALRED VERIFIED [reload-commit-decode]: Owns entity weapon/reload timestamp update, standalone terminal commit or cancellation, clip ejection, and special zero-drain events.
// UNREALRED VERIFIED [reload-role-commit-20260923]: Special reload zero at 0x4213C8..0x4213D9 and terminal pending-to-live transfer at 0x421408..0x421444 both require runtime mode 0x704E81==0. Multiplayer therefore does neither timed inventory write; terminal expiry still clears reload bit 0x100 and resets +0x139C for every role. Selected weapon mismatch 0x42136B..0x4213AD clears reload state and resets +0x13A4/+0x139C without inventory rollback or transfer. In particular it does not undo the multiplayer authority eager commit made by 0x431790.
char __cdecl rf_entity_weapon_update(int *a1)
{
  unsigned int v1; // eax
  char v3; // [esp+3h] [ebp-5h]
  int v4; // [esp+4h] [ebp-4h]

  if ( rf_weapon_has_positive_clip_size(a1[169]) )
  {
    if ( a1[a1[169] + 203] <= 0 )
    {
      v3 = 1;
      if ( sub_438AC0((int)a1) )
      {
        if ( (rf_fpgun_action_is_active(a1[1292], 0)
           || rf_fpgun_action_is_active(a1[1292], 1u)
           || rf_fpgun_state_is_resident(a1[1292], 2))
          && a1[169] != rf_weapon_id_flamethrower )
        {
          v3 = 0;
        }
        if ( *(_DWORD *)(a1[1292] + 3968) != -1 )
          v3 = 0;
      }
      else
      {
        v3 = rf_multiplayer_runtime_mode != 1;
      }
      if ( v3 == 1 )
      {
        if ( rf_entity_weapon_firing_byte_is_set(a1[11], a1[169]) )
          rf_entity_stop_weapon_firing(a1[11], a1[169]);
        rf_weapon_reload_request((int)a1, v3, 0);
      }
    }
    LOBYTE(v1) = rf_entity_reload_in_progress((int)a1);
    if ( (_BYTE)v1 )
    {
      if ( rf_entity_is_dead((int)a1) )
      {
        v1 = a1[516] & 0xFFFFFEFF;
        a1[516] = v1;
      }
      else
      {
        if ( rf_replicator_has_elapsed(a1 + 1256) )
        {
          rf_weapon_present_reload_clip_ejection((int)a1, (int)&rf_weapon_records + 1360 * a1[169]);
          rf_replicator_reset(a1 + 1256);
        }
        v4 = a1[169];
        if ( a1[1260] == v4 )
        {
          if ( rf_replicator_has_elapsed(a1 + 1257) )
          {
            if ( !rf_multiplayer_runtime_mode )
              a1[v4 + 203] = 0;
            rf_replicator_reset(a1 + 1257);
          }
          LOBYTE(v1) = rf_replicator_has_elapsed(a1 + 1255);
          if ( (unsigned __int8)v1 == 1 )
          {
            if ( !rf_multiplayer_runtime_mode )
            {
              a1[v4 + 203] = a1[1258];
              a1[dword_912024[340 * v4] + 171] = a1[1259];
            }
            a1[516] &= ~0x100u;
            LOBYTE(v1) = (unsigned __int8)rf_replicator_reset(a1 + 1255);
          }
        }
        else
        {
          a1[516] &= ~0x100u;
          rf_replicator_reset(a1 + 1257);
          LOBYTE(v1) = (unsigned __int8)rf_replicator_reset(a1 + 1255);
        }
      }
    }
  }
  else
  {
    a1[516] &= ~0x100u;
    LOBYTE(v1) = (_BYTE)a1;
  }
  return v1;
}

