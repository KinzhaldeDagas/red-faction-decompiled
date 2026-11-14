// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004222C0 rf_entity_begin_weapon_firing_state_and_effects
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl(full entity HANDLE,signed weaponIndex,LOWBYTE alternate), void/no status. Native signed0<=weaponIndex<64 required before ENTITY
// resolution; miss exits. Reload431740 EXACT AL1 exits; other bytes pass. Runtime BYTE704E81 EXACT1 additionally calls player-associated438AC0 and, if any-nonzero, calls4A8380 with
// entity pushed as ignored extra DWORD. Literal caller would reject FULL EAX0, but verified native4A8380 reads no argument and ALWAYS returns FULL EAX1, so this stub cannot veto.
// Runtime bytes other than1 bypass this stub branch. All these checks precede own writes.  Snapshot existing firing BYTE[entity+1132+weapon]. ANY nonzero means already active and is
// left unchanged, including byte2; zero means newly active: writes EXACT1, disarms entity+1228 deadline, sets entity DWORD+2000 mask0x2000 ONLY when alternate LOWBYTE==1 (otherwise
// clears), then arms entity+1876 random inclusive300..1300ms. Existing active calls skip this entire initialization, but continue sound/cooldown/effect logic. Weapon
// record=912000+1360*index.  Global presentation-suppression BYTE704E83 EXACT1 skips generic audio prefix; every other byte enters. Newly active AND signed record DWORD+508>-1 plays
// start event: code reads entity ammo DWORD[684+4*DWORD(record+36)]; signed ammo>0 bypasses next instruction, otherwise loads DWORD(record+612) into ECX and executes LITERAL OR
// ECX,0x20 then JZ, without storing flags back. OR cannot produce zero, so no ammo/flag value suppresses the start event. Calls435BB0(entity,&localPoint), ignoring return (helper may
// normalize negative entity+1296 prop index; fallback writes COMMON position), resolves446F60(record+508,0), and calls positional568250(event,&localPoint,FLOAT1,shared17F10B0,0).
// Result ignored.  Still in generic prefix, cached voice entity DWORD+2076!=-1 skips remaining generic voice handling, even if stale/not playing. If exactly-1: signed record
// DWORD+516>-1 AND FULL EAX nonzero voice-is-playing(entity+2080) stops that voice and writes entity+2080=-1; a nonplaying stale handle is not cleared. Class-mask800 predicate40D2C0
// ANY nonzero uses deadline path only: if entity+2072 is-armed predicate ANY nonzero, leaves it; otherwise arms from FTOL2SSE(record FLOAT+512 * DOUBLE1000), no +0.5/intermediate
// float32/finite/positive guard. Armed elapsed deadlines are not rearmed merely for being elapsed. Class predicate0 instead selects Foley record DWORD+356 when alternate BYTE==1,
// else+352; class DWORD+1872!=-1 causes SECOND Foley selection overriding first, preserving first random consumption. Plays4BCDD0 at by-value entity point+2004,event,1,0 without
// selected-1 guard and stores playback FULL EAX at entity+2076 including failure-1. Runtime BYTE ANY nonzero AND entity DWORD+2068 mask0x20000 emits extra event85 through same
// wrapper at COMMON position+60, ignored result.  After generic-prefix bypass/completion, ALWAYS calls4DD720(original full handle); player-list lookup result is stored only to unused
// local and does not gate effects. Riot-stick511020 ANY nonzero enters independent path: if suppression BYTE!=1 requests body action4352A0(entity full handle,3), ignoring result. For
// i=0,1 computes native FTOL2SSE(record FLOAT[344+4*i]*DOUBLE1000+DOUBLE0.5), with no intermediate float32 store; only signed converted milliseconds>0 arms embedded entity+1216+4*i
// deadline, otherwise old deadline remains. These conversions/positive tests occur even when suppression==1. If suppression!=1, ALWAYS first chooses Foley record+352; alternate
// BYTE==1 AND NORMAL source record+352!=-1 then chooses SECOND source+356 overriding it (guard is not on alternate source), preserving both selections. Plays object sound at COMMON
// position+60,1,0 with no selected-1 guard; runtime ANY nonzero/mask0x20000 emits another event85, so generic and Riot paths can each emit85 in one call. Regardless of suppression,
// arms entity+1208 with511280(weapon,LOWBYTE1), including zero/negative returned milliseconds; selector is always1, independent of alternate byte.  Finally flame-flag511040 ANY
// nonzero is tested independently of Riot path. If entity DWORD slot+5076==-1, calls4C3220 with native stack(parent full handle+44,position+60,direction+96,EXTRA FLOAT10,EXTRA
// FLOAT1), cleans20, stores returned ring INDEX at+5076. Verified callee reads ONLY first THREE parameters: final two pushed floats are ignored extras, not extra prototype arguments.
// All four emitter allocations may fail while a slot index still returns. Existing any-not-1 slot instead calls4C36C0(slot,1), without own index validation. BOTH branches then
// call4227E0(entity) without testing allocation results or enable-helper return. No rollback of firing flag/deadlines/voices/effect slot or later dependent calls, and no own
// projectile creation/ammo consumption/success return.
void __cdecl rf_entity_begin_weapon_firing_state_and_effects(int a1, unsigned int a2, char a3)
{
  unsigned int v3; // eax
  int sound_by_index; // eax
  int v5; // eax
  int four_emitters; // eax
  float v7; // [esp-Ch] [ebp-58h] BYREF
  int v8; // [esp-8h] [ebp-54h]
  float *v9; // [esp-4h] [ebp-50h]
  int v10; // [esp+0h] [ebp-4Ch]
  float v11; // [esp+4h] [ebp-48h]
  float v12; // [esp+8h] [ebp-44h]
  int v13; // [esp+1Ch] [ebp-30h]
  int v14; // [esp+20h] [ebp-2Ch]
  int v15; // [esp+24h] [ebp-28h]
  int i; // [esp+28h] [ebp-24h]
  int v17; // [esp+2Ch] [ebp-20h]
  float out_position[3]; // [esp+30h] [ebp-1Ch] BYREF
  unsigned int *entity; // [esp+3Ch] [ebp-10h]
  char v20; // [esp+43h] [ebp-9h]
  char *v21; // [esp+44h] [ebp-8h]
  _DWORD *v22; // [esp+48h] [ebp-4h]

  if ( a2 < 0x40 )
  {
    entity = (unsigned int *)rf_entity_resolve_handle(a1);
    if ( entity )
    {
      if ( !rf_entity_reload_in_progress((int)entity) )
      {
        if ( rf_multiplayer_runtime_mode != 1
          || !sub_438AC0((int)entity)
          || (v12 = *(float *)&entity, rf_constant_one_4A8380()) )
        {
          v20 = 1;
          if ( !*((_BYTE *)entity + a2 + 1132) )
          {
            v20 = 0;
            *((_BYTE *)entity + a2 + 1132) = 1;
            rf_replicator_reset(entity + 307);
            if ( a3 == 1 )
              v3 = entity[500] | 0x2000;
            else
              v3 = entity[500] & 0xFFFFDFFF;
            entity[500] = v3;
            rf_timestamp_arm_random_inclusive_milliseconds((int *)entity + 469, 300, 1300);
          }
          v21 = (char *)&rf_weapon_records + 1360 * a2;
          if ( byte_704E83 != 1 )
          {
            if ( *((int *)v21 + 127) > -1 && !v20 )
            {
              rf_vector3_default_construct_noop(out_position);
              rf_entity_primary_tag_position(entity, out_position);
              v12 = 0.0;
              v11 = COERCE_FLOAT(&unk_17F10B0);
              *(float *)&v10 = 1.0;
              v9 = out_position;
              sound_by_index = rf_foley_get_sound_by_index(*((_DWORD *)v21 + 127), 0);
              rf_gamesound_play_positional_event(sound_by_index, out_position, 1.0, (int)&unk_17F10B0, 0);
            }
            if ( entity[519] == -1 )
            {
              if ( *((int *)v21 + 129) > -1 && rf_gamesound_voice_is_playing(entity[520]) )
              {
                rf_gamesound_stop_voice_handle(entity[520]);
                entity[520] = -1;
              }
              if ( rf_entity_class_flags724_has_mask800((int)entity) )
              {
                if ( !rf_replicator_is_armed(entity + 518) )
                  rf_replicator_arm_milliseconds((int *)entity + 518, (int)(*((float *)v21 + 128) * 1000.0));
              }
              else
              {
                if ( a3 == 1 )
                  v17 = rf_foley_choose_random_sound(*((_DWORD *)v21 + 89));
                else
                  v17 = rf_foley_choose_random_sound(*((_DWORD *)v21 + 88));
                if ( *(_DWORD *)(entity[165] + 1872) != -1 )
                  v17 = rf_foley_choose_random_sound(*(_DWORD *)(entity[165] + 1872));
                v12 = 0.0;
                v11 = 1.0;
                v10 = v17;
                rf_vector3_copy_return_destination(&v7, (float *)entity + 501);
                v5 = rf_sound_event_play_for_object_view((int)entity, v7, v8, (int)v9, v10, v11, v12);
                entity[519] = v5;
                if ( rf_multiplayer_runtime_mode && (entity[517] & 0x20000) != 0 )
                {
                  v12 = 0.0;
                  v11 = 1.0;
                  v10 = 85;
                  rf_vector3_copy_return_destination(&v7, (float *)entity + 15);
                  rf_sound_event_play_for_object_view((int)entity, v7, v8, (int)v9, v10, v11, v12);
                }
              }
            }
          }
          v22 = sub_4DD720(a1);
          if ( rf_weapon_is_riot_stick(a2) )
          {
            if ( byte_704E83 != 1 )
              rf_entity_request_forced_body_action_by_handle(entity[11], 3);
            for ( i = 0; i < 2; ++i )
            {
              v15 = (int)(*(float *)&v21[4 * i + 344] * 1000.0 + 0.5);
              if ( v15 > 0 )
                rf_replicator_arm_milliseconds((int *)&entity[i + 304], v15);
            }
            if ( byte_704E83 != 1 )
            {
              v13 = rf_foley_choose_random_sound(*((_DWORD *)v21 + 88));
              if ( a3 == 1 && *((_DWORD *)v21 + 88) != -1 )
                v13 = rf_foley_choose_random_sound(*((_DWORD *)v21 + 89));
              v12 = 0.0;
              v11 = 1.0;
              v10 = v13;
              rf_vector3_copy_return_destination(&v7, (float *)entity + 15);
              rf_sound_event_play_for_object_view((int)entity, v7, v8, (int)v9, v10, v11, v12);
              if ( rf_multiplayer_runtime_mode && (entity[517] & 0x20000) != 0 )
              {
                v12 = 0.0;
                v11 = 1.0;
                v10 = 85;
                rf_vector3_copy_return_destination(&v7, (float *)entity + 15);
                rf_sound_event_play_for_object_view((int)entity, v7, v8, (int)v9, v10, v11, v12);
              }
            }
            v14 = rf_weapon_fire_wait_milliseconds(a2, 1);
            rf_replicator_arm_milliseconds((int *)entity + 302, v14);
          }
          if ( rf_weapon_has_flame_flag(a2) )
          {
            if ( entity[1269] == -1 )
            {
              v12 = 1.0;
              v11 = 10.0;
              four_emitters = rf_firing_effect_ring_create_four_emitters(
                                entity[11],
                                (float *)entity + 15,
                                (float *)entity + 24);
              entity[1269] = four_emitters;
            }
            else
            {
              rf_firing_effect_slot_set_enabled_for_mode(entity[1269], 1);
            }
            rf_entity_update_selected_weapon_firing_effect_pose(entity);
          }
        }
      }
    }
  }
}

