// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005059A0 rf_trigger_activation_eligible
// UNREALRED VERIFIED [mission-startup-20261020] NPC policy at+0x2C4 is numeric: 0 requires player flag unless weapon-activation flag is set; 2 requires activating UID in trigger links; 3 excludes player-associated objects; 4 requires an entity with Use vehicle classification AND player association. Other byte values impose no additional policy. Flag8 startup triggers are always excluded from ordinary eligibility, independently of flag4 auto-Use ownership.
// UNREALRED VERIFIED [trigger-geometry-20261020] Same-frame flag0x40, disabled0x10, finite activation limit and cooldown gate repeated physical admissions. Trigger class labels such as Trigger Door vs Trigger Event do not create a separate native open/closed latch here. UnrealRed routes decoded door physical and Use activation through the shared trigger commit path and retains occupants while disabled for re-enable scanning.
// UNREALRED VERIFIED [trigger-inside-time-20261021] Eligibility rejection (including same-frame bit0x40 or absent current Use mode for bit1) returns through504B30 shared InsideTime reset. A historical Use press is not persistent authorization; each query carries its own mode. Physical prefilters can skip504B30 entirely and then do not reset this timer.
bool __cdecl rf_trigger_activation_eligible(int *a1, _DWORD *a2, char a3)
{
  int v4; // [esp+4h] [ebp-14h]
  int v5; // [esp+8h] [ebp-10h]
  int i; // [esp+Ch] [ebp-Ch]
  char v7; // [esp+13h] [ebp-5h]
  _DWORD *v8; // [esp+14h] [ebp-4h]

  if ( (a1[172] & 0x10) != 0 )
    return 0;
  if ( (a1[172] & 0x40) != 0 )
    return 0;
  if ( a1[168] >= a1[169] && a1[169] != -1 )
    return 0;
  if ( (a1[172] & 8) != 0 )
    return 0;
  if ( !rf_replicator_has_elapsed(a1 + 166) )
    return 0;
  if ( !a1[177] && !rf_object_has_player_flag((int)a2) && (a1[172] & 2) == 0 )
    return 0;
  if ( a1[177] == 3 && rf_object_is_player_associated((int)a2) == 1 )
    return 0;
  if ( a1[177] == 4 )
  {
    v8 = (_DWORD *)rf_entity_resolve_handle(a2[11]);
    if ( !v8 )
      return 0;
    if ( !rf_object_is_use_vehicle(v8) )
      return 0;
    if ( !rf_object_is_player_associated((int)a2) )
      return 0;
  }
  if ( a1[177] == 2 )
  {
    v7 = 0;
    for ( i = 0; i < rf_receiver_get_first_dword(a1 + 181); ++i )
    {
      if ( *(_DWORD *)sub_552200(a1 + 181, i) == a2[11] )
      {
        v7 = 1;
        break;
      }
    }
    if ( !v7 )
      return 0;
  }
  if ( (a1[172] & 1) != 0 && !a3 )
    return 0;
  if ( (a1[172] & 2) != 0 )
  {
    if ( a2[9] != 2 )
      return 0;
    v5 = rf_object_resolve_handle(a2[12]);
    if ( !rf_object_is_player_associated(v5) )
      return 0;
  }
  if ( (a1[172] & 0x80) != 0 )
  {
    v4 = rf_entity_resolve_handle(a2[11]);
    if ( !v4 )
      return 0;
    if ( !rf_entity_has_attached_use_vehicle(v4) )
      return 0;
  }
  return a1[193] == -1 || rf_clutter_find_by_uid(a1[193]);
}

