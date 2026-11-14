// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040C3C0 rf_ai_try_pick_up_corpse
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): Cdecl(required AI block,32-bit corpse HANDLE, not a corpse pointer). Returns explicit AL0/1. Resolves type7; rejects missing, corpse signed class
// index+672==-1, corpse DWORD+720 nonzero, class table DWORD683C6C+5396*index missing mask0x20000, currently stored block handle+1212 resolving to any corpse, retiring predicate
// EXACT AL1, authored corpse identifier+32==9643, or source crouch EXACT AL1. No upper/lower class range beyond -1. If source has player flag (any nonzero AL), also requires block
// timer+1208 elapsed, and if entity player pointer+5168 nonnull rejects player armed-timer1216/1220 predicate, armed player+184, or custom-action busy EXACT AL1. Writes handle to
// block+1212, plays event32(0,0.0,1.0), scans projectile list next+652 and detaches EVERY projectile with attachment handle+688==corpse handle: set-1, zero velocity+324, OR
// physics+424 mask0x80000000. Marks corpse hidden/inactive, calls speed selector4344D0 with ECX=source entity, request0. If player pointer exists snapshots current holstered
// predicate into player DWORD+16 mask0x40 (sets/clears), then calls436800 holster setter. Returns1 regardless of holster helper outcome. No own distance, geometry, multiplayer or
// authority test; caller owns those gates. Does not destroy corpse/projectiles.
char __cdecl rf_ai_try_pick_up_corpse(int *a1, int a2)
{
  int v3; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  _DWORD *v5; // [esp+10h] [ebp-4h]

  v5 = (_DWORD *)rf_corpse_resolve_handle_type7(a2);
  if ( !v5 )
    return 0;
  if ( v5[168] == -1 )
    return 0;
  if ( v5[180] )
    return 0;
  if ( (unk_683C6C[1349 * v5[168]] & 0x20000) == 0 )
    return 0;
  if ( rf_corpse_resolve_handle_type7(a1[303]) )
    return 0;
  if ( (unsigned __int8)rf_corpse_is_retiring((int)v5) == 1 )
    return 0;
  if ( v5[8] == 9643 )
    return 0;
  if ( rf_entity_is_crouched_state810(*a1) )
    return 0;
  if ( !rf_object_has_player_flag(*a1) )
    goto LABEL_27;
  if ( !rf_replicator_has_elapsed(a1 + 302) )
    return 0;
  v3 = *(_DWORD *)(*a1 + 5168);
  if ( !v3 )
    goto LABEL_27;
  if ( rf_player_entity_has_armed_timer1216_or1220(v3) )
    return 0;
  if ( rf_replicator_is_armed((_DWORD *)(v3 + 184)) )
    return 0;
  if ( rf_fpgun_custom_action_busy(v3) )
    return 0;
LABEL_27:
  a1[303] = a2;
  rf_gamesound_play_event(32, 0, 0.0, 1.0);
  for ( i = dword_911F74; (_UNKNOWN *)i != &unk_911CE8; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 688) == a2 )
    {
      *(_DWORD *)(i + 688) = -1;
      rf_vector3_zero_return_destination((float *)(i + 324));
      *(_DWORD *)(i + 424) |= 0x80000000;
    }
  }
  rf_object_mark_hidden_inactive((int)v5);
  sub_4344D0(*a1, 0);
  if ( *(_DWORD *)(*a1 + 5168) )
  {
    if ( rf_entity_weapon_is_holstered_for_actions(*a1) )
      *(_DWORD *)(*(_DWORD *)(*a1 + 5168) + 16) |= 0x40u;
    else
      *(_DWORD *)(*(_DWORD *)(*a1 + 5168) + 16) &= ~0x40u;
  }
  rf_entity_try_set_holster_and_stop_primary((_DWORD *)*a1);
  return 1;
}

