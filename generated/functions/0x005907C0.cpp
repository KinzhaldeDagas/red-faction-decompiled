// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005907C0 rf_dsound_play_streaming_sample
// UNREALRED VERIFIED [dsound-creation-20261028]: Arguments sample index,volume float,pan float,loop byte. Requires initialized and sample>=0. Allocates slot,creates/primes streaming DS buffer0x590960; failure-1 without additional cleanup. Copies sample metadata+520 tobackend+24,sets flag4,sets volume andpan int(pan*1000),caches volume/source index. Creates streaming timer slot0x5D06A0 with loop byte; starts DS Play flags1 ALWAYS,even nonlooping source (service routine pads/stops atEOF). Timer failure orPlay failure delegates0x58F3E0 cleanup then-1. Success issues incrementing play handle with negative-counter wrapto0. Does not validate setter results or close sample ACM handle on later stop.
int __cdecl rf_dsound_play_streaming_sample(int a1, float a2, float a3, char a4)
{
  int v5; // eax
  int *v6; // [esp+4h] [ebp-10h]
  int v7; // [esp+10h] [ebp-4h]

  if ( !unk_1BA1810 )
    return -1;
  if ( a1 < 0 )
    return -1;
  v7 = rf_dsound_allocate_or_reclaim_backend_slot();
  if ( v7 == -1 )
    return -1;
  if ( rf_dsound_create_prime_streaming_buffer_slot(a1, v7) )
    return -1;
  v6 = &unk_1BA1820[11 * v7];
  v6[6] = *((_DWORD *)&unk_1951808 + 148 * a1 + 130);
  v6[10] |= 4u;
  v5 = rf_dsound_volume_float_to_lookup_value(a2);
  (*(void (__stdcall **)(int, int))(*(_DWORD *)*v6 + 60))(*v6, v5);
  *((float *)v6 + 5) = a2;
  (*(void (__stdcall **)(int, int))(*(_DWORD *)*v6 + 64))(*v6, (int)(a3 * 1000.0));
  v6[2] = a1;
  v6[3] = rf_audio_stream_create_timer_slot(a1, v7, a4);
  if ( v6[3] < 0 || (*(int (__stdcall **)(int, _DWORD, _DWORD, int))(*(_DWORD *)*v6 + 48))(*v6, 0, 0, 1) < 0 )
  {
    rf_dsound_buffer_slot_stop_release_unless_fading(v7);
    return -1;
  }
  else
  {
    v6[4] = dword_1BA1814++;
    if ( dword_1BA1814 < 0 )
      dword_1BA1814 = 0;
    return unk_1BA1830[11 * v7];
  }
}

