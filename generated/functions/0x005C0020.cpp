// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C0020 rf_sound_backend_shutdown
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): When ready, unregisters all counted resources, dispatches mode 1 to rf_audio_shutdown_device_and_subsystems or mode 2 to 5FA060, clears the first filename byte in all 2600 records, and clears backend_ready. Registered as an atexit callback.
void __cdecl rf_sound_backend_shutdown()
{
  int i; // [esp+4h] [ebp-4h]

  if ( rf_sound_backend_ready )
  {
    rf_sound_resource_unregister_all();
    if ( rf_sound_backend_mode == 1 )
    {
      rf_audio_shutdown_device_and_subsystems();
    }
    else if ( rf_sound_backend_mode == 2 )
    {
      rf_com_audio_backend_shutdown();
    }
    for ( i = 0; i < 2600; ++i )
      rf_sound_resource_registry[64 * i] = 0;
    rf_sound_backend_ready = 0;
  }
}

