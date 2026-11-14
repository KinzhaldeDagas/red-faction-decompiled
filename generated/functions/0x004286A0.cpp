// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004286A0 rf_entity_update_directional_motion_sound_latch
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity node pose/physics, VFX rendering, secondary ammunition and attachment/detach native chains and native
// signed/x87/stack/callback ABI): Cdecl(required entity), no uniform fullEAX result despite saved unsigned type. If BOTH class pointer660 DWORD+308/+312 are EXACT-1, exit untouched.
// Otherwise438090(entity,-1) ANY nonzero required; zero exits without latch/voice cleanup. Compute lengthSquared(entity vector324) and storeFLOAT32; comparison against true DOUBLE0.1
// sends <= OR UNORDERED to OR entity2064 latchmask0x8000. ONLY ordered squaredLength>0.1 takes moving branch. If latch clear, exit; if set, test FULL EAX from
// voice-is-playing568970(entity voice2116). Any nonzero skips play, but latch still clears. FullEAX0 computes dot(vector324,COMMON matrix third row96): only ordered dot>0 selects
// class sound-group308; dot<=0 OR UNORDERED selects312. Call446F60(selectedGroup,variant0) then positional568250(returnedEvent,entity position60,FLOAT1,address17F10B0,DWORD0);
// selected group may be-1 and returned event-1 is still passed, with no alternate-direction fallback. Store voiceEAX verbatim at2116. Finally clear latchmask0x8000 whether
// already-playing or play attempt failed. No RNG/variant cycling in446F60, no voice stop/release, finite guard or rollback; near-stationary/NaN branch arms one later ordered-moving
// attempt rather than playing repeatedly.
char __cdecl rf_entity_update_directional_motion_sound_latch(int a1)
{
  unsigned int v1; // eax
  int sound_by_index; // eax
  int v3; // eax
  float v5; // [esp+Ch] [ebp-4h]

  if ( *(_DWORD *)(*(_DWORD *)(a1 + 660) + 308) != -1 || (v1 = *(_DWORD *)(a1 + 660), *(_DWORD *)(v1 + 312) != -1) )
  {
    LOBYTE(v1) = rf_entity_runtime_enabled_or_resolved_attachment(a1, -1);
    if ( (_BYTE)v1 )
    {
      v5 = rf_vector_length_squared((float *)(a1 + 324));
      if ( v5 <= 0.1 )
      {
        v1 = *(_DWORD *)(a1 + 2064) | 0x8000;
        *(_DWORD *)(a1 + 2064) = v1;
      }
      else
      {
        LOBYTE(v1) = a1;
        if ( (*(_DWORD *)(a1 + 2064) & 0x8000) != 0 )
        {
          if ( !rf_gamesound_voice_is_playing(*(_DWORD *)(a1 + 2116)) )
          {
            if ( rf_vector_dot((float *)(a1 + 324), (float *)(a1 + 96)) <= 0.0 )
              sound_by_index = rf_foley_get_sound_by_index(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 312), 0);
            else
              sound_by_index = rf_foley_get_sound_by_index(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 308), 0);
            v3 = rf_gamesound_play_positional_event(sound_by_index, (float *)(a1 + 60), 1.0, (int)&unk_17F10B0, 0);
            *(_DWORD *)(a1 + 2116) = v3;
          }
          v1 = *(_DWORD *)(a1 + 2064) & 0xFFFF7FFF;
          *(_DWORD *)(a1 + 2064) = v1;
        }
      }
    }
  }
  return v1;
}

