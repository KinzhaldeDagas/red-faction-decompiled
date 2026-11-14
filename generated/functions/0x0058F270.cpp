// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058F270 rf_audio_shutdown_device_and_subsystems
// UNREALRED VERIFIED [dsound-creation-20261028]: Only runs when overall initialized byte0x1BA1810 nonzero. Releases backend slots0x58F3B0,all sample records0x58F5D0,streaming timers0x5D07F0,then calls0x598920 and3D listener shutdown0x5ED3B0. Releases/nulls interfaces0x19514D4,0x1BA1808,0x1BA180C,0x193BBE4,primary buffer0x195166C,device0x1951804. Calls ACM driver shutdown,CoUninitialize only when COM flag0x193BBE3==1,clears overall initialized. Does not reset COM flag or sample registry count here; backend release can skip fading records. If initialized0,partial initialization resources are not handled by this routine.
void rf_audio_shutdown_device_and_subsystems()
{
  if ( unk_1BA1810 )
  {
    rf_dsound_release_all_backend_slots_wrapper();
    rf_sound_release_all_sample_records();
    rf_audio_streaming_shutdown_slots();
    rf_audio_property_extension_clear_ready_cache();
    rf_dsound3d_shutdown_if_ready();
    if ( dword_19514D4 )
    {
      (*(void (__stdcall **)(_DWORD))(*(_DWORD *)dword_19514D4 + 8))(dword_19514D4);
      dword_19514D4 = 0;
    }
    if ( dword_1BA1808 )
    {
      (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_1BA1808 + 8))(dword_1BA1808, dword_1BA1808);
      dword_1BA1808 = nullptr;
    }
    if ( dword_1BA180C )
    {
      (*(void (__stdcall **)(_DWORD *))(*dword_1BA180C + 8))(dword_1BA180C);
      dword_1BA180C = nullptr;
    }
    if ( dword_193BBE4 )
    {
      (*(void (__stdcall **)(_DWORD *))(*dword_193BBE4 + 8))(dword_193BBE4);
      dword_193BBE4 = nullptr;
    }
    if ( dword_195166C )
    {
      (*(void (__thiscall **)(_DWORD *, _DWORD *))(*dword_195166C + 8))(dword_195166C, dword_195166C);
      dword_195166C = nullptr;
    }
    if ( dword_1951670[101] )
    {
      (*(void (__stdcall **)(int))(*(_DWORD *)dword_1951670[101] + 8))(dword_1951670[101]);
      dword_1951670[101] = 0;
    }
    rf_acm_shutdown_driver_if_ready();
    if ( unk_193BBE3 == 1 )
      CoUninitialize();
    unk_1BA1810 = 0;
  }
}

