// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00591060 rf_dsound_set_volume_by_play_handle
// UNREALRED VERIFIED [dsound-buffers-20261028]: Resolves handle; if valid slot and buffernonnull,calls SetVolume+60 using0x590440 lookup,then stores ORIGINAL float atrecord+20 even when HRESULT negative or lookup clamped it. Returns API result on call,otherwise resolver result. Does not update active fade step or clamp cached float.
int __cdecl rf_dsound_set_volume_by_play_handle(int a1, float a2)
{
  int result; // eax
  int v3; // eax
  int v4; // [esp+4h] [ebp-4h]

  result = rf_dsound_find_buffer_slot_by_play_handle(a1);
  v4 = result;
  if ( result >= 0 )
  {
    if ( unk_1BA1820[11 * result] )
    {
      v3 = rf_dsound_volume_float_to_lookup_value(a2);
      result = (*(int (__stdcall **)(int, int))(*(_DWORD *)unk_1BA1820[11 * v4] + 60))(unk_1BA1820[11 * v4], v3);
      *((float *)&unk_1BA1834 + 11 * v4) = a2;
    }
  }
  return result;
}

