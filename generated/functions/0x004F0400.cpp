// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F0400 rf_application_initialize_core_subsystems
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, UI panel switches,startup/frame/shutdown state,shared position codec boundaries and native return/argument ABI,original ECX/stack flow and PE bytes): No-argument void ordered startup wrapper: build/version initialization,4F0420 platform/filesystem/renderer/network initialization, HUD late fonts, GeoMod execution-queue globals,4460E0 (resets6615F8=-1 and bytes6E6DDE/6E6DDF=0). Does not inspect returned network/initializer status, add rollback or create a game level itself.
void rf_application_initialize_core_subsystems()
{
  rf_build_version_initialize();
  rf_application_initialize_platform_renderer_network();
  rf_hud_late_font_initialize();
  rf_geomod_execution_queue_global_init();
  rf_ui_panel_stack_reset_depth_and_flags();
}

