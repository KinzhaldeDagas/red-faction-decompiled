// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591130 rf_dsound_set_frequency_if_playing
// UNREALRED VERIFIED [dsound-buffers-20261028]: Arguments play handle,frequency integer. Resolves handle but DOES NOT validate result before indexing DS pointer,so invalid handle can access slot-1. Calls GetStatus+36; if success and playing bit1,calls SetFrequency+68. If GetStatus fails,formats local error message and returns sprintf character count,not HRESULT. Success but stopped returns GetStatus result without changing frequency. No frequency range check.
int __cdecl rf_dsound_set_frequency_if_playing(int a1, int a2)
{
  int result; // eax
  const char *v3; // eax
  int v4; // [esp+0h] [ebp-110h] BYREF
  int v5; // [esp+4h] [ebp-10Ch]
  char Buffer[256]; // [esp+8h] [ebp-108h] BYREF
  int buffer_slot_by_play_handle; // [esp+10Ch] [ebp-4h]

  buffer_slot_by_play_handle = rf_dsound_find_buffer_slot_by_play_handle(a1);
  result = (*(int (__stdcall **)(int, int *))(*(_DWORD *)unk_1BA1820[11 * buffer_slot_by_play_handle] + 36))(
             unk_1BA1820[11 * buffer_slot_by_play_handle],
             &v4);
  v5 = result;
  if ( result >= 0 )
  {
    if ( (v4 & 1) != 0 )
      return (*(int (__stdcall **)(int, int))(*(_DWORD *)unk_1BA1820[11 * buffer_slot_by_play_handle] + 68))(
               unk_1BA1820[11 * buffer_slot_by_play_handle],
               a2);
  }
  else
  {
    v3 = rf_dsound_hresult_name_string(v5);
    return sprintf(Buffer, "GetStatus failed with return value %s\n", v3);
  }
  return result;
}

