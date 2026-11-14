// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040A3C0 sub_40A3C0
// UNREALRED VERIFIED [lan-ai-damage-source-20261028] Damage response resolves the supplied source identifier through rf_object_resolve_handle at 0x40A4DC and rejects self at 0x40A519. The source player-flag test at 0x40A4F6 only selects an addition of literal double 0.10000000149011612 to the float damage argument; it is not an admission requirement, and the downstream significance of that adjustment is not established. Same-friendliness non-player-source suppression at 0x40A647..0x40A670 runs only when BOTH multiplayer-runtime and split-screen bytes are zero. MP/split-screen branches bypass that suppression. Preserve other recipient state/class/mode gates; this does not establish Unreal bot sight/reaction timing parity.
char __cdecl sub_40A3C0(int *Character, int a2, float a3, char a4)
{
  int v4; // eax
  float v6; // [esp+4h] [ebp-20h]
  float v7; // [esp+4h] [ebp-20h]
  float v8; // [esp+8h] [ebp-1Ch]
  float v9; // [esp+8h] [ebp-1Ch]
  float v10; // [esp+8h] [ebp-1Ch]
  int v11; // [esp+Ch] [ebp-18h]
  int v12; // [esp+14h] [ebp-10h]
  int v13; // [esp+18h] [ebp-Ch]
  char v14; // [esp+1Eh] [ebp-6h]
  char v15; // [esp+1Fh] [ebp-5h]
  int v16; // [esp+20h] [ebp-4h]

  LOBYTE(v4) = (_BYTE)Character;
  if ( Character[160] == 1
    || Character[160] == 9
    || Character[160] == 8
    || (LOBYTE(v4) = (_BYTE)Character, Character[160] == 13) )
  {
    if ( a4 == 1 && Character[160] == 13 )
    {
      v6 = rf_random_float_range(5.0, 10.0);
      LOBYTE(v4) = (unsigned __int8)sub_40B1A0(Character, v6, 0);
    }
  }
  else
  {
    LOBYTE(v4) = rf_entity_is_nonplayer_sentient_or_runtime_enabled(*Character);
    if ( (_BYTE)v4 )
    {
      LOBYTE(v4) = rf_entity_has_jeep_flag(*Character);
      if ( (unsigned __int8)v4 != 1 )
      {
        if ( rf_entity_has_humanoid_flag(*Character) && a4 == 1 && !rf_entity_class_flags724_has_mask4000000(*Character) )
        {
          v7 = rf_random_float_range(5.0, 10.0);
          LOBYTE(v4) = (unsigned __int8)sub_40B1A0(Character, v7, 0);
        }
        else
        {
          v4 = rf_object_resolve_handle(a2);
          v16 = v4;
          if ( v4 )
          {
            rf_object_has_player_flag(v4);
            LOBYTE(v4) = (_BYTE)Character;
            if ( *(_DWORD *)(*Character + 44) != a2 )
            {
              rf_ai_cancel_tracked_body_action(Character);
              rf_ai_clear_scripted_animation_context(Character);
              if ( rf_entity_speech_voice_is_playing(*Character) )
                rf_entity_stop_speech_voice(*Character);
              v14 = 1;
              v15 = 0;
              if ( rf_multiplayer_runtime_mode || rf_splitscreen_runtime_active )
              {
                if ( rand() >= 10922 )
                {
                  if ( *(float *)(*Character + 52) > 25.0 && !(rand() % 5) )
                    Character[332] |= (unsigned int)&unk_1000000;
                }
                else
                {
                  v15 = 1;
                }
              }
              if ( rf_object_is_player_associated(v16) == 1 )
              {
                if ( v15 || sub_40B6D0(Character) != 1 )
                {
                  v8 = rf_random_float_range(60.0, 120.0);
                  sub_40AC80(Character, a2, v8);
                }
                else
                {
                  v14 = 1;
                }
              }
              LOBYTE(v4) = rf_multiplayer_runtime_mode;
              if ( !rf_multiplayer_runtime_mode && !rf_splitscreen_runtime_active )
              {
                v4 = *Character;
                if ( *(_DWORD *)(*Character + 504) == *(_DWORD *)(v16 + 504) )
                {
                  LOBYTE(v4) = rf_object_is_player_associated(v16);
                  if ( !(_BYTE)v4 )
                    v14 = 0;
                }
              }
              if ( v14 == 1 )
              {
                v13 = a2;
                v12 = rf_entity_resolve_handle(a2);
                if ( v12 )
                {
                  if ( rf_entity_class_use_is4(v12) )
                  {
                    v11 = sub_435170(v12);
                    if ( rf_object_resolve_handle(v11) )
                      v13 = v11;
                  }
                }
                if ( !v15 && sub_40B6D0(Character) )
                {
                  if ( rf_entity_has_humanoid_flag(*Character)
                    && !rf_ai_primary_flag20_without_secondary((int)Character) )
                  {
                    if ( Character[296] == 2 && Character[173] == 2 )
                    {
                      LOBYTE(v4) = rf_ai_select_secondary11_after_reload_or_route_retry(Character);
                      return v4;
                    }
                    if ( !(rand() % 4) )
                    {
                      v10 = rf_random_float_range(2.0, 3.0);
                      LOBYTE(v4) = sub_40AC80(Character, v13, v10);
                      return v4;
                    }
                  }
                  if ( Character[176] != v13 )
                    sub_40BA80(Character, v13);
                  rf_replicator_arm_milliseconds(Character + 143, 0);
                  LOBYTE(v4) = sub_40B2D0(Character);
                }
                else
                {
                  v9 = rf_random_float_range(60.0, 120.0);
                  LOBYTE(v4) = sub_40AC80(Character, v13, v9);
                }
              }
            }
          }
        }
      }
    }
  }
  return v4;
}

