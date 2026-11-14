// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004ECAA0 rf_player_preload_selected_weapon_animation_files
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model cache fallback, material replacement, leg animation transitions and native caller ABI): Cdecl player, unused middle argument, weapon index. Skips dedicated byte exactly1, nonlocal player, index outside0..63, empty weapon RFString+64, or player+4224 already equal to index. Constructs unused inclusive substring(0,length-5), resolves selected mesh ignoring result, preloads three state and twelve action files with NULL buffer/zero extra DWORD. Entity class is player+24, stride5396: loops signed counts at1896+4*weapon and2152+4*weapon through pointers2408+4*weapon and2664+4*weapon;52-byte entries, filename RFString+8. Destroys temporary string including SEH cleanup. Does not update player+4224; no own NULL/short-name/class/list-pointer checks.
void __cdecl rf_player_preload_selected_weapon_animation_files(_DWORD *a1, int a2, unsigned int a3)
{
  unsigned int v3; // eax
  const char *v4; // eax
  const char *v5; // eax
  char *v6; // [esp+14h] [ebp-20h]
  _DWORD v7[2]; // [esp+18h] [ebp-1Ch] BYREF
  const char **v8; // [esp+20h] [ebp-14h]
  int i; // [esp+24h] [ebp-10h]
  int v10; // [esp+30h] [ebp-4h]

  if ( byte_704E83 != 1 && a1 == (_DWORD *)rf_local_fpgun_player && a3 < 0x40 )
  {
    v8 = (const char **)((char *)&rf_weapon_records + 1360 * a3);
    if ( rf_string_length_from_cstr(v8 + 16) )
    {
      if ( a3 != a1[1056] )
      {
        v3 = rf_string_length_from_cstr(v8 + 16);
        rf_string_substring_inclusive(v8 + 16, v7, 0, v3 - 5);
        v10 = 0;
        rf_fpgun_selected_mesh_resolve(a1, a3);
        for ( i = 0; i < 3; ++i )
          rf_weapon_preload_named_animation_file(a3, (char *)rf_fpgun_state_names[i], nullptr, 0, 1);
        for ( i = 0; i < 12; ++i )
          rf_weapon_preload_named_animation_file(a3, (char *)rf_fpgun_action_names[i], nullptr, 0, 0);
        v6 = &rf_entity_info_definitions[5396 * a1[6]];
        for ( i = 0; i < *(_DWORD *)&v6[4 * a3 + 1896]; ++i )
        {
          v4 = rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)&v6[4 * a3 + 2408] + 52 * i + 8));
          rf_rfa_load_raw_file(v4, nullptr);
        }
        for ( i = 0; i < *(_DWORD *)&v6[4 * a3 + 2152]; ++i )
        {
          v5 = rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)&v6[4 * a3 + 2664] + 52 * i + 8));
          rf_rfa_load_raw_file(v5, nullptr);
        }
        v10 = -1;
        rf_string_destroy_buffer(v7);
      }
    }
  }
}

