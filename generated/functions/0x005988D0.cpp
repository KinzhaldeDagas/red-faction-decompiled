// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005988D0 rf_audio_environment_set_preset_id
// UNREALRED VERIFIED [audio-properties-20261028]: Requires ready byte0x1BCA304,else-1. Calls Set vtable+16 on cached property interface,GUID0x656390,property11,instanceNULL/length0,data ADDRESS OF FIRST STACK ARGUMENT,length4. Actual payload is the full32-bit argument slot,despite current char decompiler prototype; does not mask or validate enum0..25. Negative HRESULT-1,nonnegative0. Does not update global selected preset0x1BCA308 itself or consult cached mute flag.
int __cdecl rf_audio_environment_set_preset_id(char a1)
{
  if ( !byte_1BCA304[0] )
    return -1;
  if ( (*(int (__thiscall **)(_DWORD *, _DWORD *, void *, int, _DWORD, _DWORD, char *, int))(*dword_1BCA300 + 16))(
         dword_1BCA300,
         dword_1BCA300,
         &unk_656390,
         11,
         0,
         0,
         &a1,
         4) < 0 )
    return -1;
  return 0;
}

