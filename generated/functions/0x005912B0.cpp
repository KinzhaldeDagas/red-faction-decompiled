// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005912B0 rf_dsound_get_frequency_by_play_handle
// UNREALRED VERIFIED [dsound-buffers-20261028]: Arguments play handle,output DWORD pointer (currently decompiled asint). Resolves handle,invalid-1. Calls DS GetFrequency vtable+32 with caller output pointer; negative HRESULT-1,else0. No buffer/output null checks; does not change playback frequency.
int __cdecl rf_dsound_get_frequency_by_play_handle(int a1, int a2)
{
  int buffer_slot_by_play_handle; // [esp+4h] [ebp-4h]

  buffer_slot_by_play_handle = rf_dsound_find_buffer_slot_by_play_handle(a1);
  if ( buffer_slot_by_play_handle < 0 )
    return -1;
  if ( (*(int (__stdcall **)(int, int))(*(_DWORD *)unk_1BA1820[11 * buffer_slot_by_play_handle] + 32))(
         unk_1BA1820[11 * buffer_slot_by_play_handle],
         a2) >= 0 )
    return 0;
  return -1;
}

