// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590D60 rf_dsound_service_fade_slot
// UNREALRED VERIFIED [dsound-buffers-20261028]: Argument slot. Only proceeds when0x590550 says hardware playing. If timer+36 elapsed0x55F2B0,arms next deadline offset75,subtracts cached step+32 from cached volume+20. Positive volume converts through0x590440 and SetVolume+60,ignoring HRESULT except incidental return. Nonpositive clears fade mask8 then calls0x58F3E0 to release. Does not catch up multiple missed ticks,process paused/stopped fades or acquire lock. Return byte path-dependent,not success.
char __cdecl rf_dsound_service_fade_slot(int a1)
{
  int is_playing; // eax
  int v2; // eax
  int *v4; // [esp+4h] [ebp-4h]

  is_playing = rf_dsound_buffer_slot_is_playing(a1);
  if ( is_playing )
  {
    v4 = &unk_1BA1820[11 * a1];
    LOBYTE(is_playing) = rf_clock_deadline_has_elapsed_half_period(v4 + 9);
    if ( (unsigned __int8)is_playing == 1 )
    {
      rf_clock_deadline_set_wrapped_offset(v4 + 9, 75);
      *((float *)v4 + 5) = *((float *)v4 + 5) - *((float *)v4 + 8);
      if ( *((float *)v4 + 5) > 0.0 )
      {
        v2 = rf_dsound_volume_float_to_lookup_value(*((float *)v4 + 5));
        LOBYTE(is_playing) = (*(char (__stdcall **)(int, int))(*(_DWORD *)*v4 + 60))(*v4, v2);
      }
      else
      {
        v4[10] &= ~8u;
        LOBYTE(is_playing) = (unsigned __int8)rf_dsound_buffer_slot_stop_release_unless_fading(a1);
      }
    }
  }
  return is_playing;
}

