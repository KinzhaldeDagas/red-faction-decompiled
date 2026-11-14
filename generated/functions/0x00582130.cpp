// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00582130 rf_renderer_project_world_point_screen_dispatch
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, numeric states, stack ABI and callers): For backend102, forwards point and two output float pointers to5C5740 and returns its byte boolean. Other renderer backends return0 without writing outputs.
char __cdecl rf_renderer_project_world_point_screen_dispatch(float *a1, float *a2, float *a3)
{
  if ( dword_187CC9C == 102 )
    return rf_renderer_project_world_point_to_screen(a1, a2, a3);
  else
    return 0;
}

