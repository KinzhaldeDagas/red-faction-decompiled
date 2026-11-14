// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD3A0 rf_event_sound_forward
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] event_sound forward callback, vtable 0x63DFEC slot +4. Requires cached resource +0x2CC != -1. Positive target identifier +0x2E4 uses 0x4BC680 then resolved record+0x2C through rf_entity_resolve_handle and replaces that entity speech voice via 0x4376C0(...,0); does not publish event-local active/voice/deadline in that branch. Otherwise stop event voice +0x2D0 only when playing, start cached resource nonpositionally iff distance +0x2D4 == 0 (finite nonzero, including negative, uses positional owner+0x40), arm +0x2E0 iff duration +0x2D8 >0 for trunc(seconds*1000), and set active byte +0x2DD=1 even if playback returns -1.
void __thiscall rf_event_sound_forward(int this)
{
  int v2; // [esp+10h] [ebp-8h]
  int v3; // [esp+14h] [ebp-4h]

  if ( *(_DWORD *)(this + 716) != -1 )
  {
    if ( *(int *)(this + 740) <= 0 )
    {
      if ( rf_gamesound_voice_is_playing(*(_DWORD *)(this + 720)) )
      {
        rf_gamesound_stop_voice_handle(*(_DWORD *)(this + 720));
        *(_DWORD *)(this + 720) = -1;
      }
      if ( *(float *)(this + 724) == 0.0 )
      {
        *(_DWORD *)(this + 720) = rf_gamesound_play_event(*(_DWORD *)(this + 716), 0, 0.0, 1.0);
        if ( *(float *)(this + 728) > 0.0 )
          rf_replicator_arm_milliseconds((int *)(this + 736), (int)(*(float *)(this + 728) * 1000.0));
      }
      else
      {
        *(_DWORD *)(this + 720) = rf_gamesound_play_positional_event(
                                    *(_DWORD *)(this + 716),
                                    (float *)(this + 64),
                                    1.0,
                                    (int)flt_17F10B0,
                                    0);
        if ( *(float *)(this + 728) > 0.0 )
          rf_replicator_arm_milliseconds((int *)(this + 736), (int)(*(float *)(this + 728) * 1000.0));
      }
      *(_BYTE *)(this + 733) = 1;
    }
    else
    {
      v3 = rf_object_find_by_saved_identifier(*(_DWORD *)(this + 740));
      if ( v3 )
      {
        v2 = rf_entity_resolve_handle(*(_DWORD *)(v3 + 44));
        if ( v2 )
          rf_entity_replace_speech_voice(v2, *(_DWORD *)(this + 716), 0);
      }
    }
  }
}

