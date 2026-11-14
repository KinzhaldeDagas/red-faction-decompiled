// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00420B40 rf_entity_play_damage_or_once_death_sound
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Cdecl(required entity,float magnitude); EAX/AL is path-dependent pointer/predicate/Foley/playback residue, not uniform success. Only ORDERED
// entity FLOAT health+52<=0 AND gameplay class(+660) DWORD+292!=-1 enters once-only branch: if entity DWORD+2064 mask4 already set, exits. Otherwise chooses Foley sound from
// DIFFERENT object pointer entity+668 DWORD+292, plays via4BCDD0(entity,by-value XYZ from entity+2004,event,1.0,0.0), then ORs entity+2064 mask4 REGARDLESS of selected sound-1 or
// playback failure; no current-voice/dead predicate or timer test in this branch. Health>0 OR UNORDERED, or gameplay class+292==-1, instead enters rate-limited branch. Dead
// predicate433F60 any-nonzero invokes player-associated438AC0; both nonzero together suppress. Numeric entity DWORD+1312 exactly1 or17 suppresses. Otherwise requires embedded
// entity+5208 deadline elapsed ANY nonzero and arms it1000ms BEFORE Foley selection/current-voice testing. Only ORDERED magnitude>DOUBLE0.3 selects Foley source object(+668)
// DWORD+368; equality/less/NaN uses+364. Selected-1 exits with deadline still armed. Otherwise FULL EAX nonzero from voice-is-playing568970(entity DWORD+2056) suppresses playback;
// FULL EAX0 plays same seven-slot by-value-point sound call at entity+2004. Playback return is not saved to an entity voice field here. No pointer/class/sound validation or rollback
// of timer/mask, and no health/mode write.
char __cdecl rf_entity_play_damage_or_once_death_sound(int a1, float a2)
{
  int is_playing; // eax
  float v4; // [esp-10h] [ebp-24h] BYREF
  int v5; // [esp-Ch] [ebp-20h]
  int v6; // [esp-8h] [ebp-1Ch]
  int v7; // [esp-4h] [ebp-18h]
  float v8; // [esp+0h] [ebp-14h]
  float v9; // [esp+4h] [ebp-10h]
  int v10; // [esp+10h] [ebp-4h]

  if ( *(float *)(a1 + 52) > 0.0 || *(_DWORD *)(*(_DWORD *)(a1 + 660) + 292) == -1 )
  {
    LOBYTE(is_playing) = rf_entity_is_dead(a1);
    if ( !(_BYTE)is_playing || (LOBYTE(is_playing) = sub_438AC0(a1), !(_BYTE)is_playing) )
    {
      if ( *(_DWORD *)(a1 + 1312) != 1 )
      {
        LOBYTE(is_playing) = a1;
        if ( *(_DWORD *)(a1 + 1312) != 17 )
        {
          LOBYTE(is_playing) = rf_replicator_has_elapsed((int *)(a1 + 5208));
          if ( (_BYTE)is_playing )
          {
            rf_replicator_arm_milliseconds((int *)(a1 + 5208), 1000);
            v10 = -1;
            is_playing = a2 <= 0.3
                       ? rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(a1 + 668) + 364))
                       : rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(a1 + 668) + 368));
            v10 = is_playing;
            if ( is_playing != -1 )
            {
              is_playing = rf_gamesound_voice_is_playing(*(_DWORD *)(a1 + 2056));
              if ( !is_playing )
              {
                v9 = 0.0;
                v8 = 1.0;
                v7 = v10;
                rf_vector3_copy_return_destination(&v4, (float *)(a1 + 2004));
                LOBYTE(is_playing) = rf_sound_event_play_for_object_view(a1, v4, v5, v6, v7, v8, v9);
              }
            }
          }
        }
      }
    }
  }
  else
  {
    LOBYTE(is_playing) = a1;
    if ( (*(_DWORD *)(a1 + 2064) & 4) == 0 )
    {
      v9 = 0.0;
      v8 = 1.0;
      v7 = rf_foley_choose_random_sound(*(_DWORD *)(*(_DWORD *)(a1 + 668) + 292));
      rf_vector3_copy_return_destination(&v4, (float *)(a1 + 2004));
      rf_sound_event_play_for_object_view(a1, v4, v5, v6, v7, v8, v9);
      *(_DWORD *)(a1 + 2064) |= 4u;
      LOBYTE(is_playing) = a1;
    }
  }
  return is_playing;
}

