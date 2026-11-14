// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FD550 rf_event_sound_update
// UNREALRED VERIFIED [sound-event-duration-continuation-20261027] event_sound update callback, vtable 0x63DFEC slot +0xC. Run common delayed/special update first; continue only when active byte +0x2DD is exactly 1. Recreate only a literal -1 voice handle +0x2D0, lazily loading primary string +0x2B8 if resource +0x2CC is -1. Failed load/play clears active. For finite distance, recovery uses positional only when +0x2D4>0 (zero/negative use nonpositional), unlike forward/reverse start which compare ==0. Maintain positional source only for positive distance. Positive +0x2D8 and elapsed +0x2E0 invoke virtual slot +8, the reverse callback 0x4FD6E0, which may play alternate sound instead of stopping. This body neither tests backend completion for a non--1 handle nor rearms duration on recovery.
void __thiscall rf_event_sound_update(int this)
{
  const char *v1; // eax
  float distance; // [esp+0h] [ebp-10h]

  rf_mission_event_update_delayed_and_special((char *)this);
  if ( *(_BYTE *)(this + 733) == 1 )
  {
    if ( *(_DWORD *)(this + 720) == -1 )
    {
      if ( *(_DWORD *)(this + 716) == -1 )
      {
        distance = *(float *)(this + 724);
        v1 = rf_string_object_c_str_or_empty((const void *)(this + 696));
        *(_DWORD *)(this + 716) = rf_sound_resource_load(v1, distance, 1.0, 1.0);
        if ( *(_DWORD *)(this + 716) == -1 )
        {
          *(_BYTE *)(this + 733) = 0;
          return;
        }
      }
      if ( *(float *)(this + 724) <= 0.0 )
        *(_DWORD *)(this + 720) = rf_gamesound_play_event(*(_DWORD *)(this + 716), 0, 0.0, 1.0);
      else
        *(_DWORD *)(this + 720) = rf_gamesound_play_positional_event(
                                    *(_DWORD *)(this + 716),
                                    (float *)(this + 64),
                                    1.0,
                                    (int)flt_17F10B0,
                                    0);
    }
    if ( *(_DWORD *)(this + 720) == -1 )
    {
      *(_BYTE *)(this + 733) = 0;
    }
    else
    {
      if ( *(float *)(this + 724) > 0.0 )
        rf_positioned_voice_update(*(_DWORD *)(this + 720), (float *)(this + 64), (int)flt_17F10B0, 1.0);
      if ( *(float *)(this + 728) > 0.0 && rf_replicator_has_elapsed((int *)(this + 736)) )
        (*(void (__thiscall **)(int))(*(_DWORD *)this + 8))(this);
    }
  }
}

