// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598950 rf_audio_property_extension_initialize
// UNREALRED VERIFIED [dsound-playback-20261028]: If ready byte0x1BCA304==1 returns0. Requires mode getter0x5915C0 nonzero; copies BORROWED main property interface0x19514D4 into cache0x1BCA300 via getter,without AddRef. Null-1. Calls QuerySupport vtable+20(GUID0x656390,property1); requires nonnegative HRESULT andsupportmask3 bothbits. Success sets ready1 andcachedfield0x1BCA2FC=0,returns0. Failure Release on cached borrowed pointer,sets cacheNULL,clears extension mode0x591610 andready,returns-1. Does NOT clear main property global0x19514D4 after Release; ownership differs from successful shutdown. No parameter payload initialization in this body.
int rf_audio_property_extension_initialize()
{
  int v1; // [esp+4h] [ebp-4h] BYREF

  v1 = 0;
  if ( byte_1BCA304[0] == 1 )
    return 0;
  if ( !rf_audio_get_property_extension_mode_byte() )
    return -1;
  dword_1BCA300 = (_DWORD *)rf_dsound_get_property_interface_pointer();
  if ( !dword_1BCA300 )
    return -1;
  if ( (*(int (__stdcall **)(_DWORD *, void *, int, int *))(*dword_1BCA300 + 20))(dword_1BCA300, &unk_656390, 1, &v1) >= 0
    && (v1 & 3) == 3 )
  {
    byte_1BCA304[0] = 1;
    unk_1BCA2FC = 0;
    return 0;
  }
  else
  {
    if ( dword_1BCA300 )
    {
      (*(void (__stdcall **)(_DWORD *))(*dword_1BCA300 + 8))(dword_1BCA300);
      dword_1BCA300 = nullptr;
    }
    rf_audio_clear_property_extension_mode();
    byte_1BCA304[0] = 0;
    return -1;
  }
}

