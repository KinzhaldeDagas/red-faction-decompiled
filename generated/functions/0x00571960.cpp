// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00571960 rf_renderer_shutdown_backend_and_release_fonts
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): No args. If selector187CC9C==102 calls5C2650 guarded D3D teardown,then ALWAYS calls rf_font_release_all_loaded_records and returns its incidental result. Non102 still releases fonts. Does not itself clear generic initialized flags,screen dimensions,selector or gamma globals.
int rf_renderer_shutdown_backend_and_release_fonts()
{
  if ( dword_187CC9C == 102 )
    rf_d3d8_shutdown_backend_if_initialized();
  return rf_font_release_all_loaded_records();
}

