// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005107C0 rf_projectile_get_selected_damage_with_owner_scale
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Resolves projectile owner UID+48 as generic object and asks4BCF40 player-association predicate (NULL safe). Selector LOW BYTE EXACTLY1 selects alt damage, others primary. Either nonzero multiplayer runtime byte OR splitscreen byte selects multiplayer fields: primary SP+264/multi+268, alt SP+272/multi+276 of info pointer projectile+660. Player association result EXACTLY1 returns raw selected F32. Otherwise multiplies by info F32+288, explicitly stores/reloads F32 and returns ST0. Parser508990 proves four $Damage/$Damage Multi/$Alt Damage/$Alt Damage Multi fields; factor+288 is a runtime field, distinct from authored $AI Damage Scale fields+280/+284. No projectile/info NULL
// guard or finite/clamp validation.
double __cdecl rf_projectile_get_selected_damage_with_owner_scale(int a1, char a2)
{
  int v7; // [esp+10h] [ebp-4h]

  v7 = rf_object_resolve_handle(*(_DWORD *)(a1 + 48));
  if ( rf_object_is_player_associated(v7) == 1 )
  {
    if ( a2 == 1 )
    {
      if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
        return *(float *)(*(_DWORD *)(a1 + 660) + 276);
      else
        return *(float *)(*(_DWORD *)(a1 + 660) + 272);
    }
    else if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
    {
      return *(float *)(*(_DWORD *)(a1 + 660) + 268);
    }
    else
    {
      return *(float *)(*(_DWORD *)(a1 + 660) + 264);
    }
  }
  else if ( a2 == 1 )
  {
    if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
      return (float)(*(float *)(*(_DWORD *)(a1 + 660) + 276) * *(float *)(*(_DWORD *)(a1 + 660) + 288));
    else
      return (float)(*(float *)(*(_DWORD *)(a1 + 660) + 272) * *(float *)(*(_DWORD *)(a1 + 660) + 288));
  }
  else if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
  {
    return (float)(*(float *)(*(_DWORD *)(a1 + 660) + 268) * *(float *)(*(_DWORD *)(a1 + 660) + 288));
  }
  else
  {
    return (float)(*(float *)(*(_DWORD *)(a1 + 660) + 264) * *(float *)(*(_DWORD *)(a1 + 660) + 288));
  }
}

