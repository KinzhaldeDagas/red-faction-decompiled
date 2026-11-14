// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F1D90 rf_application_initialize_run_and_shutdown
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): No arguments, returns integer0 after normal cleanup. Sets BYTE182A379=1; applies command-line startup4F1EE0; sets registry default software path Volition/Red Faction. Dedicated BYTE704E83 EXACT1 builds Red Faction Dedicated Server title and initializes window(Volition,title,1,1); otherwise probes4A6760 (constant AL0) and initializes(Volition,Red Faction,1,0). Calls core startup4F0400,4EFBF0(0); only dedicated BYTE==0 clears CD root/adds music archive. Requests panel1 with0. Benchmark state92DE1C EXACT2 invokes timedemo-step(NULL), else EXACT3 framerate-step(NULL). Loops4F2590 until nonzero, then4F2530 application cleanup followed by4F1EC0 renderer/audio/window shutdown.
// No explicit ECX/stack receiver supplied to cleanup; corrected its inherited false-thiscall/unused-result type. Does not propagate initializer/cleanup return values or implement a second Win32 message loop here.
int rf_application_initialize_run_and_shutdown()
{
  char v0; // al
  char Buffer[1028]; // [esp+0h] [ebp-408h] BYREF

  unk_182A379 = 1;
  rf_application_apply_command_line_startup_state();
  rf_registry_set_default_software_path("Volition", "Red Faction");
  if ( byte_704E83 == 1 )
  {
    sprintf(Buffer, "%s Dedicated Server", "Red Faction");
    rf_window_initialize_thread_and_optional_hooks("Volition", Buffer, 1, 1);
  }
  else
  {
    v0 = constant_return_false_al_4A6760();
    rf_window_initialize_thread_and_optional_hooks("Volition", "Red Faction", v0 == 0, 0);
  }
  rf_application_initialize_core_subsystems();
  rf_localization_initialize_language_and_load(0);
  if ( !byte_704E83 )
    rf_cd_clear_root_and_add_music_archive();
  rf_ui_request_panel_immediate(1, 0);
  if ( unk_92DE1C == 2 )
  {
    rf_timedemo_command_line_state_step(nullptr);
  }
  else if ( unk_92DE1C == 3 )
  {
    rf_framerate_test_command_line_state_step(nullptr);
  }
  while ( !rf_application_run_frame_and_test_exit_panel() )
    ;
  rf_application_cleanup_before_backend_shutdown();
  rf_application_shutdown_renderer_audio_and_window();
  return 0;
}

