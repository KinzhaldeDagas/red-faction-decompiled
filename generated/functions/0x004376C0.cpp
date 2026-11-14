// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004376C0 rf_entity_replace_speech_voice
// UNREALRED VERIFIED [entity-speech-lifecycle-20261027] Entity-owned speech replacement, reached from Message event entity branch at 0x4FE850. Reject sound id -1 or dead/null owner before touching the old voice. If owner+0x1400 != -1, stop that handle and clear it without first querying playback. When third argument is zero, predicate 0x40D280 is true, and split-screen is inactive, arm owner+0x140C at 0 ms and store queried sound duration (seconds) at +0x1408. Those gates control animation timing only: positional audio is still attempted with gain 1, source owner+0x7D4, auxiliary argument 0x17F10B0 and final argument 0. Store returned handle (including allocation failure -1) at +0x1400. This function neither enqueues HUD captions nor arms persona cue timers.
// UNREALRED VERIFIED [combat-entity-speech-20261111]: Shared entity-lifetime speech owner, not AI-mode17-only. Reject selectedSound==-1 or dead BEFORE touching old voice. Otherwise stop any retained voice handle and store-1; for arg3==0,40D280(modelhandle plus classmodelkind2),!split, arm Entity+140C0 BEFORE duration query and storefloat seconds+1408. Split/arg3 only skip these writes; they do not clear old countdown/action or suppress positional audio. Play selected sound once at Entity+7D4,gain1 and retain returned handle including-1 failure. Native568250 fourth pointer unused; velocity is supplied later in5684D0 update. Stop/playing/completion do not implicitly reset duration/action.
void __cdecl rf_entity_replace_speech_voice(int a1, int a2, char a3)
{
  bool v3; // [esp+Fh] [ebp-1h]

  if ( a2 != -1 && !rf_entity_is_dead(a1) )
  {
    if ( *(_DWORD *)(a1 + 5120) != -1 )
    {
      rf_gamesound_stop_voice_handle(*(_DWORD *)(a1 + 5120));
      *(_DWORD *)(a1 + 5120) = -1;
    }
    v3 = 0;
    if ( !a3 )
      v3 = rf_entity_admits_speech_body_actions(a1);
    if ( v3 && !rf_splitscreen_runtime_active )
    {
      rf_replicator_arm_milliseconds((int *)(a1 + 5132), 0);
      *(float *)(a1 + 5128) = rf_sound_query_duration(a2);
    }
    *(_DWORD *)(a1 + 5120) = rf_gamesound_play_positional_event(a2, (float *)(a1 + 2004), 1.0, (int)&unk_17F10B0, 0);
  }
}

