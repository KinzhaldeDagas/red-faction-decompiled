// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004030D0 rf_ai_play_global_elapsed_mode3_speech
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI ready/idle/unholster/transient request chains, original float constants and exact native predicates and
// native signed/x87/stack/callback ABI): One required AI block with entity at+0. Owner DWORD+2068 mask0x200 suppresses. Reject dead predicate EXACT AL1 or attached-use-vehicle
// predicate EXACT1. Requires global deadline6663E4 elapsed nonzero AL and mode DWORD+640==3. Predicate401EF0(block) nonzero chooses registry sound helper441430, else441400, passing
// owner class(+660) DWORD+1780. Replaces speech(owner,chosenSound,0) even for sound-1; resets global deadline afterwards regardless of playback outcome, making it a shared one-shot
// across entities. No own speech-currently-playing, multiplayer, distance, local-player or authority gate. EAX/AL path-dependent, not uniform success.
unsigned __int8 __cdecl rf_ai_play_global_elapsed_mode3_speech(int *a1)
{
  unsigned __int8 result; // al
  int v2; // [esp+0h] [ebp-4h]

  result = (unsigned __int8)a1;
  if ( (*(_DWORD *)(*a1 + 2068) & 0x200) == 0 )
  {
    result = rf_entity_is_dead(*a1);
    if ( result != 1 )
    {
      result = rf_entity_has_attached_use_vehicle(*a1);
      if ( result != 1 )
      {
        result = rf_replicator_has_elapsed(&dword_6663E4);
        if ( result )
        {
          if ( a1[160] == 3 )
          {
            if ( rf_ai_has_unholstered_mode3_peer_on_same_target(a1) )
              v2 = rf_foley_registry_choose_sound_441430(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
            else
              v2 = rf_foley_registry_choose_sound_441400(*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1780));
            rf_entity_replace_speech_voice(*a1, v2, 0);
            return (unsigned __int8)rf_replicator_reset(&dword_6663E4);
          }
        }
      }
    }
  }
  return result;
}

