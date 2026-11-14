// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00421BA0 rf_character_apply_damage
// UNREALRED VERIFIED [combat-transport-20260930] Fresh disassembly confirms multiplayer mode==1 AND server authority==1 chooses the two-damage-per-armor branch: damage<=2*armor subtracts damage*0.5 from armor; otherwise zero armor and subtract damage-2*oldArmor from life. The other branch remains the SP damage-type path; this function alone does not prove a blanket no-client-damage gate. Separate Unreal process transport checks must compare the committed health/armor results, not infer delivery from a connection or mode flag.
// UNREALRED VERIFIED [lan-ai-damage-source-20261028] After pool/flinch/presentation work, 0x422192..0x4221CA invokes sub_40A3C0(recipient AI at entity+0x2A0, supplied source identifier, original damage argument, 0) only when the recipient lacks direct common player flag 0x8 and retains positive life. This call does not require the source to be a human player. Player-owned Unreal LAN bots use an explicit enhanced-AI adaptation; do not remove native recipient gates on the strength of this source observation.
// UNREALRED VERIFIED [lan-body-credit-20261029] After resulting life<=0, multiplayer==1/server==1 and existing common+0x270 attacker byte==-1, resolve supplied source handle first against CURRENT player entity handles via4DD720; if found copy Player+0x1200 network record,+0x14 byte, else call4DBBE0 for the retained dead-body handle history. Nonlethal hits do not write this byte in this routine. Existing non--1 byte is retained; this alone does not establish last-nonlethal-attacker retention or a timeout.
// UNREALRED VERIFIED [indirect-source-20261029] Lethal fire with source -1 may resolve an active fire record or secondary object into Entity+0x144C; the subsequent MP attacker-byte lookup STILL uses original source argument a3. Do not copy the separately resolved burn/death metadata into multiplayer frag attribution without another verified writer.
// UNREALRED VERIFIED [combat-burn-owner-20261104]: Fire ignition runs after pool mutation/source death metadata. Existing fire association suppresses replacement. Armor max0 or current/max<.5 or forced0x8000; reject use-vehicle, attached vehicle,438AC0 and4377E0 (together ALL native player-flag bodies). Resolved source438AC0 with no spread0x2000 bypasses friendliness; other resolved entity source requires exact common+504 inequality, unresolved source uses anonymous allocation. ignore_fire class flag suppresses panic only. Transient spread/forced flags clear afterward; do not turn ignore_fire into damage immunity or infer MP team equality.
// UNREALRED VERIFIED [combat-burn-duration-20261104]: After successful automatic ignition with ignore_fire absent, raw421FF5/422063 samples random float[5,10] and421FFD/42206B fstp overwrites the stack duration argument before40B1A0; a3 is literal0. The decompiled apparent fixed5.0 is misleading. High-armor spread branch samples[3,5] at4220A6 and stores return at4220AE before40AC80. Preserve these draw phases even when host AI timer/route ownership is explicitly incomplete; explicit4FCA70 ignition does not enter either reaction.
double __cdecl rf_character_apply_damage(int a1, float a2, int a3, int a4, int a5)
{
  float v6; // [esp+4h] [ebp-3Ch]
  float v7; // [esp+4h] [ebp-3Ch]
  float v8; // [esp+8h] [ebp-38h]
  int v9; // [esp+10h] [ebp-30h]
  int v10; // [esp+14h] [ebp-2Ch]
  int v11; // [esp+18h] [ebp-28h]
  _DWORD *v12; // [esp+1Ch] [ebp-24h]
  int v13; // [esp+20h] [ebp-20h]
  float v14; // [esp+24h] [ebp-1Ch]
  float v15; // [esp+28h] [ebp-18h]
  float v16; // [esp+2Ch] [ebp-14h]
  float v17; // [esp+30h] [ebp-10h]
  float v18; // [esp+34h] [ebp-Ch]
  float v19; // [esp+38h] [ebp-8h]
  float v20; // [esp+3Ch] [ebp-4h]

  v17 = a2;
  v20 = *(float *)(a1 + 52);
  if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 )
  {
    if ( a2 <= *(float *)(a1 + 56) + *(float *)(a1 + 56) )
    {
      *(float *)(a1 + 56) = *(float *)(a1 + 56) - a2 * 0.5;
    }
    else
    {
      v15 = *(float *)(a1 + 56) + *(float *)(a1 + 56);
      *(float *)(a1 + 56) = 0.0;
      v16 = a2 - v15;
      *(float *)(a1 + 52) = *(float *)(a1 + 52) - v16;
    }
  }
  else
  {
    if ( a4 != -1 )
      a2 = a2 * *(float *)(*(_DWORD *)(a1 + 660) + 4 * a4 + 5096);
    if ( *(float *)(a1 + 56) <= 0.0 )
    {
      v18 = a2;
    }
    else
    {
      v14 = rf_character_resolve_sp_armor_absorption(a1, a2, a4);
      *(float *)(a1 + 56) = *(float *)(a1 + 56) - v14;
      v18 = a2 - v14;
    }
    *(float *)(a1 + 52) = *(float *)(a1 + 52) - v18;
    *(float *)(a1 + 1852) = *(float *)&dword_6FC428;
  }
  if ( *(float *)(a1 + 52) >= 0.0 && *(float *)(a1 + 52) <= 0.5 )
    *(float *)(a1 + 52) = -0.1;
  if ( *(float *)(a1 + 52) <= 0.0 )
  {
    if ( a4 == 4 && a3 == -1 && *(_DWORD *)(a1 + 5080) )
    {
      *(_DWORD *)(a1 + 5196) = sub_43FCD0(*(_DWORD *)(a1 + 5080));
    }
    else if ( a4 == 4 && a3 == -1 && a5 != -1 )
    {
      v13 = sub_4316E0(a5);
      *(_DWORD *)(a1 + 5196) = v13 ? *(_DWORD *)(v13 + 44) : -1;
    }
    else
    {
      *(_DWORD *)(a1 + 5196) = a3;
    }
    if ( rf_multiplayer_runtime_mode == 1 && rf_multiplayer_server_authority == 1 && *(char *)(a1 + 624) == -1 )
    {
      v12 = sub_4DD720(a3);
      if ( v12 )
        *(_BYTE *)(a1 + 624) = *(_BYTE *)(v12[1152] + 20);
      else
        *(_BYTE *)(a1 + 624) = sub_4DBBE0(a3);
    }
  }
  if ( v17 > 5.0 )
    rf_character_try_damage_flinch((_DWORD *)a1);
  v19 = v17 / *(float *)(*(_DWORD *)(a1 + 660) + 68);
  if ( v19 > 0.001 && a4 != 10 )
    rf_entity_play_damage_or_once_death_sound(a1, v19);
  if ( a4 == 4 )
  {
    if ( !*(_DWORD *)(a1 + 5080) )
    {
      if ( *(float *)(*(_DWORD *)(a1 + 660) + 72) == 0.0
        || *(float *)(a1 + 56) / *(float *)(*(_DWORD *)(a1 + 660) + 72) < 0.5
        || (*(_DWORD *)(a1 + 2068) & 0x8000) != 0 )
      {
        if ( !rf_object_is_use_vehicle((_DWORD *)a1)
          && !rf_entity_has_attached_use_vehicle(a1)
          && !sub_438AC0(a1)
          && !rf_object_player_flag_without_player_context(a1) )
        {
          v10 = a3;
          if ( a3 == -1 && a5 != -1 )
          {
            v9 = sub_4316E0(a5);
            if ( v9 )
              v10 = *(_DWORD *)(v9 + 44);
          }
          v11 = rf_entity_resolve_handle(v10);
          if ( v11 )
          {
            if ( sub_438AC0(v11) && (*(_DWORD *)(a1 + 2068) & 0x2000) == 0 )
            {
              *(_DWORD *)(a1 + 5080) = sub_43E970(*(_DWORD *)(a1 + 44), v10);
            }
            else if ( *(_DWORD *)(v11 + 504) != *(_DWORD *)(a1 + 504) )
            {
              *(_DWORD *)(a1 + 5080) = sub_43E970(*(_DWORD *)(a1 + 44), v10);
            }
            if ( *(_DWORD *)(a1 + 5080) && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1832) & 0x10) == 0 )
            {
              v6 = rf_random_float_range(5.0, 10.0);
              sub_40B1A0((int *)(a1 + 672), v6, 0);
            }
          }
          else
          {
            *(_DWORD *)(a1 + 5080) = sub_43E970(*(_DWORD *)(a1 + 44), -1);
            if ( *(_DWORD *)(a1 + 5080) && (*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1832) & 0x10) == 0 )
            {
              v7 = rf_random_float_range(5.0, 10.0);
              sub_40B1A0((int *)(a1 + 672), v7, 0);
            }
          }
        }
      }
      else if ( (*(_DWORD *)(a1 + 2068) & 0x2000) != 0 )
      {
        v8 = rf_random_float_range(3.0, 5.0);
        sub_40AC80((int *)(a1 + 672), a3, v8);
      }
    }
    *(_DWORD *)(a1 + 2068) &= ~0x2000u;
    *(_DWORD *)(a1 + 2068) &= ~0x8000u;
  }
  if ( *(int *)(a1 + 2064) >= 0 && a4 == 6 && !rf_gamesound_voice_is_playing(*(_DWORD *)(a1 + 2132)) )
    *(_DWORD *)(a1 + 2132) = rf_gamesound_play_positional_event(35, (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
  if ( sub_438AC0(a1) && v20 > 0.0 && a2 > 0.0 && a4 != 10 )
    rf_player_hud_damage_tint_red();
  if ( !rf_object_has_player_flag(a1) && *(float *)(a1 + 52) > 0.0 )
    sub_40A3C0((int *)(a1 + 672), a3, v17, 0);
  return a2;
}

