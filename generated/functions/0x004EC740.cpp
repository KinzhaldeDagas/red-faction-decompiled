// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EC740 rf_fpgun_selected_mesh_resolve
// UNREALRED VERIFIED [fpgun-vmesh-decode]: Returns the ordinary selected mesh at definition +0x48, with two verified special-table substitutions; it does not return Spark VFX +0x500.
int __cdecl rf_fpgun_selected_mesh_resolve(_DWORD *a1, unsigned int a2)
{
  int v3; // eax
  int v4; // [esp+0h] [ebp-10h]
  int i; // [esp+4h] [ebp-Ch]
  int v6; // [esp+8h] [ebp-8h]
  char *v7; // [esp+Ch] [ebp-4h]

  if ( a1 != (_DWORD *)rf_local_fpgun_player )
    return 0;
  if ( a2 == -1 )
  {
    if ( a1[13] )
      rf_player_weapon_reset_noop();
    return 0;
  }
  else if ( a2 < 0x40 )
  {
    v7 = (char *)&rf_weapon_records + 1360 * a2;
    if ( rf_string_length_from_cstr((const char **)v7 + 16) )
    {
      if ( a2 == dword_911CC4 && a1[1056] == unk_911C98 || a2 == unk_911C98 && a1[1056] == dword_911CC4 )
      {
        a1[1056] = a2;
        return a1[13];
      }
      else
      {
        if ( a2 != a1[1056] && a1[13] )
        {
          a1[13] = 0;
          a1[14] = 0;
        }
        if ( a1[13] )
        {
          return a1[13];
        }
        else
        {
          v4 = a2;
          if ( a2 == unk_911C88 )
          {
            v4 = dword_911C78;
          }
          else if ( a2 == unk_911C98 )
          {
            v4 = dword_911CC4;
          }
          v6 = -1;
          for ( i = 0; i < 32; ++i )
          {
            if ( v4 == rf_weapon_cycle_slots_weapon_index[4 * i] )
            {
              v6 = i;
              break;
            }
          }
          if ( v6 == -1 )
          {
            a1[13] = unk_912048[340 * v4];
          }
          else
          {
            if ( a2 == unk_911C88 )
              v3 = unk_87C118[4 * v6];
            else
              v3 = rf_weapon_cycle_slots_runtime_icon[4 * v6];
            a1[13] = v3;
          }
          if ( !a1[13] )
            rf_fatal_error_show_message_and_exit(
              "D:\\projects\\rf_pc\\gamesrc\\player\\player_fpgun.cpp",
              3893,
              "Failed to load weapon mesh!");
          a1[992] = -1;
          rf_replicator_reset(a1 + 993);
          if ( *((_DWORD *)v7 + 25) != -1 )
            rf_renderer_bind_texture_for_level_warmup(*((_DWORD *)v7 + 25));
          a1[14] = 0;
          a1[1056] = a2;
          if ( sub_4EF770() == 1 && a2 == dword_87FC1C )
            rf_undercover_apply_local_weapon_skin_profile();
          return a1[13];
        }
      }
    }
    else
    {
      return a1[13];
    }
  }
  else
  {
    return 0;
  }
}

