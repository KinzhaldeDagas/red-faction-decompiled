// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005987D0 rf_audio_environment_restore_saved_room_level
// UNREALRED VERIFIED [audio-properties-20261028]: If ready byte0x1BCA304 nonzero and muted flag0x1BCA2FC set,calls Set vtable+16(GUID0x656390,property2,input savedDWORD0x1BCA2F8,length4),then clears muted flag regardless HRESULT. Other paths leave flag untouched and return incidental ready/flag value. Does not refetch current hardware value or validate saved state; no automatic retry after failed restore.
int rf_audio_environment_restore_saved_room_level()
{
  int result; // eax

  result = byte_1BCA304[0];
  if ( byte_1BCA304[0] )
  {
    if ( unk_1BCA2FC )
    {
      result = (*(int (__stdcall **)(_DWORD *, void *, int, _DWORD, _DWORD, void *, int))(*dword_1BCA300 + 16))(
                 dword_1BCA300,
                 &unk_656390,
                 2,
                 0,
                 0,
                 &unk_1BCA2F8,
                 4);
      unk_1BCA2FC = 0;
    }
  }
  return result;
}

