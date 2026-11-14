// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598740 rf_audio_environment_save_room_level_and_mute
// UNREALRED VERIFIED [audio-properties-20261028]: Only when ready byte0x1BCA304 nonzero and muted flag0x1BCA2FC==0. Property interface cached at0x1BCA300,GUID0x656390. Calls Get vtable+12 for property2 into saved DWORD0x1BCA2F8,length4,returned-byte output. If Get succeeds,calls Set vtable+16 property2,input signedDWORD-10000,length4. Sets muted flag1 REGARDLESS Get or Set failure. Return final HRESULT or prior ready flag,path-dependent. No byte-count validation,pointer guard or rollback; saved value can be stale when Get fails.
int rf_audio_environment_save_room_level_and_mute()
{
  int result; // eax
  int v1; // [esp+0h] [ebp-Ch] BYREF
  _BYTE v2[4]; // [esp+4h] [ebp-8h] BYREF
  int v3; // [esp+8h] [ebp-4h]

  result = byte_1BCA304[0];
  if ( byte_1BCA304[0] && !unk_1BCA2FC )
  {
    result = (*(int (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, void *, int, _BYTE *))(*dword_1BCA300 + 12))(
               dword_1BCA300,
               dword_1BCA300,
               &unk_656390,
               2,
               0,
               0,
               &unk_1BCA2F8,
               4,
               v2);
    v3 = result;
    if ( result >= 0 )
    {
      v1 = -10000;
      result = (*(int (__stdcall **)(_DWORD *, void *, int, _DWORD, _DWORD, int *, int))(*dword_1BCA300 + 16))(
                 dword_1BCA300,
                 &unk_656390,
                 2,
                 0,
                 0,
                 &v1,
                 4);
    }
    unk_1BCA2FC = 1;
  }
  return result;
}

