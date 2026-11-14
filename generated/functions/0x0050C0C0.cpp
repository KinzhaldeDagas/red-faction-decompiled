// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050C0C0 rf_weapon_present_world_impact
// UNREALRED VERIFIED [weapon-impact-decode]: Shared world-impact presentation: decal, material sound, and all authored impact VClips.
// VERIFIED [transient-projectile-light]: Shared world-impact presentation creates decals, material Foley, and authored impact VClips. Exhaustive direct xrefs to renderer point-light creation and the decoded VClip/explosion call closure prove no separate renderer impact light is created here.
unsigned __int8 __cdecl rf_weapon_present_world_impact(float *a1, char a2, char a3)
{
  unsigned __int8 result; // al
  int first_dword; // eax
  int v5; // [esp+8h] [ebp-1Ch]
  float normal[3]; // [esp+Ch] [ebp-18h] BYREF
  char v7; // [esp+1Ah] [ebp-Ah]
  bool v8; // [esp+1Bh] [ebp-9h]
  int v9; // [esp+1Ch] [ebp-8h]
  int v10; // [esp+20h] [ebp-4h]

  v8 = (*(_DWORD *)(*((_DWORD *)a1 + 165) + 612) & 0x10) != 0;
  v7 = rf_geomod_face_owner_type1_flag152_clear(*((_DWORD *)a1 + 124));
  if ( v7 == 1 && (result = v8) != 0 )
  {
    if ( a3 == 1 )
      return (unsigned __int8)rf_weapon_create_impact_decal(
                                *((_DWORD *)a1 + 166),
                                a1 + 109,
                                a1 + 81,
                                a1 + 112,
                                *((_DWORD *)a1 + 121),
                                0,
                                v7);
  }
  else
  {
    if ( a3 == 1 )
    {
      rf_weapon_create_impact_decal(*((_DWORD *)a1 + 166), a1 + 109, a1 + 81, a1 + 112, *((_DWORD *)a1 + 121), a2, v7);
      if ( v7 )
      {
        rf_vector_negate(a1 + 112, normal);
        rf_weapon_create_impact_decal(*((_DWORD *)a1 + 166), a1 + 109, a1 + 81, normal, *((_DWORD *)a1 + 121), a2, v7);
      }
    }
    v9 = *((_DWORD *)a1 + 116);
    if ( rf_projectile_flag2_damage_type_is_1_or_2((int)a1) )
      v10 = rf_foley_choose_random_sound(*(_DWORD *)(*((_DWORD *)a1 + 165) + 4 * v9 + 416));
    else
      v10 = rf_foley_choose_random_sound(*(_DWORD *)(*((_DWORD *)a1 + 165) + 4 * v9 + 376));
    if ( v10 == -1 )
    {
      v9 = 0;
      if ( rf_projectile_flag2_damage_type_is_1_or_2((int)a1) )
        v10 = rf_foley_choose_random_sound(*(_DWORD *)(*((_DWORD *)a1 + 165) + 4 * v9 + 416));
      else
        v10 = rf_foley_choose_random_sound(*(_DWORD *)(*((_DWORD *)a1 + 165) + 4 * v9 + 376));
    }
    result = rf_gamesound_play_positional_event(v10, a1 + 109, 1.0, (int)flt_17F10B0, 0);
    if ( !v7 && a3 == 1 )
    {
      result = rf_projectile_flag2_damage_type_is_1_or_2((int)a1);
      if ( !result )
      {
        v5 = *((_DWORD *)a1 + 12);
        first_dword = rf_receiver_get_first_dword(a1);
        return rf_weapon_spawn_impact_vclips(*((_DWORD *)a1 + 166), first_dword, 0, (_BYTE)a1 - 76, (int)(a1 + 112), v5);
      }
    }
  }
  return result;
}

