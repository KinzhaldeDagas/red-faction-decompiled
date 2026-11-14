// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D06A0 rf_audio_stream_create_timer_slot
// UNREALRED VERIFIED [audio-streaming-20261028]: Arguments source sample index,backend buffer index,loop byte. Finds first inactive slot; none-1. Sets flags1,source+0,buffer+4,logical cursor+12=0,ring bytes+8=2*sample output WAVEFORMAT avgBytesPerSec+8. Nonzero loop byte sets mask2. Creates250ms periodic timer,user=slot; success stores timer+16 andreturns slot. Timer failure clears flags but leaves other assigned fields,returns-1. Does not create/play/prime DS buffer,rewind source,reset silence-drain+20,validate sample/buffer indices or acquire critical section.
int __cdecl rf_audio_stream_create_timer_slot(int a1, int a2, char a3)
{
  int dwUser; // [esp+0h] [ebp-8h]
  int *v5; // [esp+4h] [ebp-4h]

  dwUser = rf_audio_stream_find_inactive_slot();
  if ( dwUser < 0 )
    return -1;
  v5 = &unk_1E012F0[7 * dwUser];
  v5[6] = 1;
  *v5 = a1;
  v5[1] = a2;
  v5[3] = 0;
  v5[2] = 2 * *(_DWORD *)(unk_1951A20[148 * a1] + 8);
  if ( a3 )
    v5[6] |= 2u;
  v5[4] = rf_audio_stream_start_periodic_timer(0xFAu, dwUser);
  if ( v5[4] )
    return dwUser;
  v5[6] = 0;
  return -1;
}

