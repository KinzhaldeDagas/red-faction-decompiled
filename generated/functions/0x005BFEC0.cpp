// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BFEC0 rf_sound_backend_initialize
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Loads bluebeard.bty metadata; failure raises the fatal missing-project-information message at sound.cpp:606. If argument 7 equals 1, tries backend initializer 5F9F80. Zero success selects mode 2; any nonzero result selects DirectSound mode 1 and calls its initializer, returning -1 on failure. Resets four group gains, initializes positional instances and the resource table, sets backend_ready=1, registers shutdown with atexit, and returns 0.
int __cdecl rf_sound_backend_initialize(
        int a1,
        int a2,
        unsigned __int16 a3,
        __int16 a4,
        char a5,
        char a6,
        char a7,
        char a8)
{
  int v9; // [esp+0h] [ebp-4h]

  if ( rf_bluebeard_sound_metadata_load() )
    rf_fatal_error_show_message_and_exit(
      "D:\\projects\\rf_pc\\vsdk\\sound\\sound.cpp",
      606,
      "Unable to read project sound information.  Is bluebeard.bty missing?");
  v9 = -1;
  if ( a7 == 1 )
    v9 = rf_com_audio_backend_initialize(a1);
  if ( v9 )
  {
    rf_sound_backend_mode = 1;
    if ( rf_audio_initialize_device_primary_and_modes(a1, a2, a3, a4, a5, a6, a8) )
      return -1;
  }
  else
  {
    rf_sound_backend_mode = 2;
  }
  rf_sound_group_gains_reset_unity();
  rf_positional_sound_instances_initialize_once();
  rf_sound_resource_registry_initialize_once();
  rf_sound_backend_ready = 1;
  atexit(rf_sound_backend_shutdown);
  return 0;
}

