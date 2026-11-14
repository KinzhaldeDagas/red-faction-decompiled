// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590CA0 rf_dsound_begin_fade_stop_by_play_handle
// UNREALRED VERIFIED [dsound-buffers-20261028]: Arguments play handle,duration in engine-clock units. Duration<75 delegates ordinary stop0x590C30,which can still be suppressed by an already-set fade flag. Otherwise resolves handle,sets flags mask8,arms timerDWORD+36 with offset0 via0x55F1F0,and computes fade step+32=cached volume+20 / integer(duration/75). Returns record pointer or-1. No volume/range validation; duration quantized down to whole75-unit steps.
int *__cdecl rf_dsound_begin_fade_stop_by_play_handle(int a1, int a2)
{
  int *result; // eax
  int *v3; // [esp+4h] [ebp-8h]
  int *v4; // [esp+8h] [ebp-4h]

  if ( a2 < 75 )
    return rf_dsound_stop_release_by_play_handle(a1);
  result = (int *)rf_dsound_find_buffer_slot_by_play_handle(a1);
  v4 = result;
  if ( (int)result >= 0 )
  {
    v3 = &unk_1BA1820[11 * (_DWORD)result];
    v3[10] |= 8u;
    rf_clock_deadline_set_wrapped_offset(v3 + 9, 0);
    *((float *)v3 + 8) = *((float *)v3 + 5) / (double)(a2 / 75);
    return &unk_1BA1820[11 * (_DWORD)v4];
  }
  return result;
}

