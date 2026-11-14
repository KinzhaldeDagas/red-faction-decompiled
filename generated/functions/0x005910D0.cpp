// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005910D0 rf_dsound_set_pan_by_play_handle
// UNREALRED VERIFIED [dsound-buffers-20261028]: Resolves handle; valid nonnull buffer calls SetPan+64 with int(inputfloat*1000). No clamp to API range,rounding offset,finite check or cache update. Returns API result or resolver result.
int __cdecl rf_dsound_set_pan_by_play_handle(int a1, float a2)
{
  int result; // eax

  result = rf_dsound_find_buffer_slot_by_play_handle(a1);
  if ( result >= 0 )
  {
    if ( unk_1BA1820[11 * result] )
      return (*(int (__stdcall **)(int, int))(*(_DWORD *)unk_1BA1820[11 * result] + 64))(
               unk_1BA1820[11 * result],
               (int)(a2 * 1000.0));
  }
  return result;
}

