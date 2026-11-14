// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BB070 rf_damage_dispatch
// UNREALRED VERIFIED [mission-protection-20261020] Make_Invulnerable uses the common flag4 gate here, before type-specific damage/HUD/flinch/life effects. Final bypass byte skips this gate along with other common admission checks. A mission flag must therefore not be implemented by globally disabling all forced damage or by stopping only life subtraction.
// UNREALRED VERIFIED [mission-unhide-20261020] Direct common damage dispatch does not blanket-reject common inactive. Preserve explicit damage calls; candidate exclusion belongs to specific radial/trace/AI callers. UnHide is not invulnerability.
// UNREALRED VERIFIED [lan-ai-dm-relations-20261028] The MP-authority same-team damage veto at 0x4BB168..0x4BB1A5 is conditional: sub_492030 returns the raw mode value at 0x704ED4, and mode zero jumps past the veto; sub_4B1240 returns whether game flags contain 0x200, whose enabled result also skips it. Remaining gates require two distinct resolved player records and equality of their team bytes +0x30. It is not an unconditional same-team-byte or all-AI immunity rule. Existing self-scale, spawn protection, invulnerability and damage dispatch ownership remain separate.
// UNREALRED VERIFIED [indirect-source-20261029] After common damage admission, dispatch still contains type4 clutter and type7 corpse handlers in multiplayer. The MP radial exclusion belongs to4BAA30 candidate lists; do not make clutter/corpses universally invulnerable or apply the exclusion to direct projectile/hitscan damage.
double __cdecl rf_damage_dispatch(int a1, float a2, int a3, int a4, int a5, int a6, int a7, char a8)
{
  int v9; // eax
  float v10[3]; // [esp-8h] [ebp-3Ch] BYREF
  int v11; // [esp+4h] [ebp-30h]
  float v12; // [esp+8h] [ebp-2Ch]
  float v13; // [esp+Ch] [ebp-28h]
  int v14; // [esp+10h] [ebp-24h]
  _DWORD *v15; // [esp+18h] [ebp-1Ch]
  int v16; // [esp+1Ch] [ebp-18h]
  _DWORD *v17; // [esp+20h] [ebp-14h]
  int v18; // [esp+24h] [ebp-10h]
  int v19; // [esp+28h] [ebp-Ch]
  int v20; // [esp+2Ch] [ebp-8h]
  float v21; // [esp+30h] [ebp-4h]

  v20 = rf_object_resolve_handle(a1);
  if ( !v20 )
    return 0.0;
  if ( a2 < 0.001000000047497451 )
    return 0.0;
  *(_DWORD *)(v20 + 124) |= 0x200000u;
  if ( !a8 )
  {
    if ( (*(_DWORD *)(v20 + 124) & 4) != 0 )
      return 0.0;
    v19 = rf_entity_resolve_handle(a1);
    if ( v19 && rf_entity_class_flag2000000_positive_scalar56(v19) )
      return 0.0;
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
    {
      v15 = sub_4DD720(a1);
      v17 = sub_4DD720(a3);
      if ( v15 && !rf_replicator_has_elapsed(v15 + 48) )
        return 0.0;
      if ( rf_multiplayer_game_mode_get()
        && !rf_multiplayer_game_flag200_is_set()
        && v15
        && v17
        && v15 != v17
        && *((unsigned __int8 *)v17 + 48) == *((unsigned __int8 *)v15 + 48) )
      {
        return 0.0;
      }
      if ( a1 == a3 )
        a2 = a2 * 0.75;
      v18 = 0;
      v16 = 0;
      if ( v17 )
        v18 = rf_entity_resolve_handle(v17[5]);
      if ( v15 )
        v16 = rf_entity_resolve_handle(v15[5]);
      if ( v16 && (*(_DWORD *)(v19 + 2068) & 0x40000) != 0 )
      {
        if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
        {
          v13 = 0.0;
          v12 = 1.0;
          v11 = 87;
          rf_vector3_copy_return_destination(v10, (float *)(v16 + 60));
          rf_sound_event_play_for_object_view(v16, v10[0], SLODWORD(v10[1]), SLODWORD(v10[2]), v11, v12, v13);
        }
        return 0.0;
      }
      if ( a5 == 9 && (rf_multiplayer_game_flags & 0x100) == 0 )
      {
        if ( (rf_multiplayer_game_flags & 0x80) == 0 )
          return 0.0;
        a2 = a2 * 0.5;
      }
    }
    if ( a5 != 9 )
    {
      if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
      {
        v9 = rf_object_resolve_handle(a3);
        if ( !rf_object_has_player_flag(v9) )
          a2 = a2 * flt_661234[dword_6612A4];
      }
      else if ( rf_object_is_player_associated(v20) )
      {
        a2 = a2 * flt_661224[dword_6612A4];
      }
    }
  }
  v21 = 0.0;
  v14 = *(_DWORD *)(v20 + 36);
  switch ( v14 )
  {
    case 0:
      v21 = rf_character_apply_damage(v20, a2, a3, a5, a7);
      break;
    case 2:
      *(float *)(v20 + 52) = *(float *)(v20 + 52) - a2;
      break;
    case 3:
      if ( a2 > 100.0 )
        *(float *)(v20 + 52) = *(float *)(v20 + 52) - a2;
      break;
    case 4:
      rf_clutter_apply_damage(v20, a2, a3, a5, a6);
      break;
    case 7:
      rf_corpse_apply_explosive_damage(v20, a2, a3, a5);
      break;
    default:
      break;
  }
  if ( rf_object_is_player_associated(v20) && *(float *)(v20 + 52) > 0.0 && *(float *)(v20 + 52) <= 0.5 )
    *(float *)(v20 + 52) = 0.0;
  return v21;
}

