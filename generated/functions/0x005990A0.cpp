// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005990A0 rf_audio_environment_set_all_property_fields
// UNREALRED VERIFIED [network-queues-20261028]: If borrowed IKsPropertySet global0x1BCA300 nonnull,calls Set(vtable+16) GUID0x656390,property1,no instance data,input pointer argument,length56. No ready flag,destination validation,individual property updates or returned HRESULT handling. Does not alter mute/preset cache globals.
void __cdecl rf_audio_environment_set_all_property_fields(int a1)
{
  if ( dword_1BCA300 )
    (*(int (__stdcall **)(_DWORD *, void *, int, _DWORD, _DWORD, int, int))(*dword_1BCA300 + 16))(
      dword_1BCA300,
      &unk_656390,
      1,
      0,
      0,
      a1,
      56);
}

