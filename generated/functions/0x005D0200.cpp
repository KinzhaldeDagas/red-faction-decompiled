// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D0200 rf_audio_stream_stop_slot
// UNREALRED VERIFIED [audio-streaming-20261028]: Argument slot. If backend buffer index+4>=0 and associated DS buffer pointer nonnull,calls buffer Stop vtable+72; then index=-1. Kills timer0x5CFE40, clears flags+24 and source sample index+0=-1,returns slot record pointer. Does NOT release DS buffer/source wave/ACM stream,reset ring size+8,logical cursor+12 or silence-drain counter+20. No critical section acquisition or index validation.
int *__cdecl rf_audio_stream_stop_slot(int a1)
{
  int *v2; // [esp+0h] [ebp-4h]

  v2 = &unk_1E012F0[7 * a1];
  if ( v2[1] >= 0 )
  {
    if ( unk_1BA1820[11 * v2[1]] )
      (*(void (__stdcall **)(int))(*(_DWORD *)unk_1BA1820[11 * v2[1]] + 72))(unk_1BA1820[11 * v2[1]]);
    v2[1] = -1;
  }
  rf_audio_stream_kill_slot_timer((int)v2);
  v2[6] = 0;
  *v2 = -1;
  return &unk_1E012F0[7 * a1];
}

