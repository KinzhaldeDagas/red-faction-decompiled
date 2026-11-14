// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B7230 rf_multiplayer_start_dedicated_runtime
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, packet registry/function recovery, kill/download routing, native CRC/UI/startup and original geometry
// constants and native signed/x87/stack/callback ABI): No arguments. In order sets dedicated/interlockBYTE704E83=1,runtime704E81=1,authority704E82=1,BYTE704E84=0; calls
// multiplayer_runtime_initialize(0,0),set_startup_session_flag(),geomod_finish_lightmap_generation(0),disable_world_lighting(),registers no-op4B7360 with atexit. If registry
// update-rate predicate returns0, prints localized88E348 and88E350 then calls console wait/exit helper with ONE explicit stack value1 (not decompiler garbage ECX), and branches to
// end if it returned. Otherwise command-line bool option object6F5AA0 false adds gameFlags bit0x400; true DOES NOT clear an already set bit. If resulting bit0x400 set,
// tracker_initialize_host_templates_and_pool nonzero ->network_control_cancel_pending_state with TWO explicit zero arguments; failure prints localized88E264 and clears bit0x400. No
// rollback of earlier mode/render/init effects on tracker failure, startup idempotence guard or world/level load in body.
void rf_multiplayer_start_dedicated_runtime()
{
  char v0; // cl

  byte_704E83 = 1;
  rf_multiplayer_runtime_mode = 1;
  rf_multiplayer_server_authority = 1;
  unk_704E84 = 0;
  rf_multiplayer_runtime_initialize(0, nullptr);
  rf_set_startup_session_flag();
  rf_geomod_set_finish_lightmap_generation_byte(0);
  rf_renderer_disable_world_lighting();
  atexit(rf_multiplayer_dedicated_atexit_noop);
  if ( !rf_multiplayer_registry_update_rate_is_nonzero() )
  {
    rf_console_printf_unbounded_stack2048(unk_88E348);
    rf_console_printf_unbounded_stack2048(unk_88E350);
    rf_console_wait_for_input_if_enabled_then_exit_one(v0);
  }
  if ( !rf_command_line_bool_option_is_enabled(byte_6F5AA0) )
    rf_multiplayer_game_flags |= 0x400u;
  if ( (rf_multiplayer_game_flags & 0x400) != 0 )
  {
    if ( rf_tracker_initialize_host_templates_and_pool() )
    {
      rf_network_control_cancel_pending_state();
    }
    else
    {
      rf_console_printf_unbounded_stack2048(unk_88E264);
      rf_multiplayer_game_flags &= ~0x400u;
    }
  }
}

