// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00581840 rf_console_wfar_command
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, recovered clip/projection routines, original x87 comparisons, stack arguments and PE bytes): Recovered no-argument command callback. If execution flag1809818 set,consumes numeric token through56F950(mask16,mode0),copies parsed float180A400 into663F34,and logs W far set to INTEGER-truncated value using shared18CD828 buffer. If help flag1809814 set,also logs Usage:wfar<float>. Always calls clip-plane rebuild581180 even help/no-execute. Changes663F34 rather than ordinary far-distance18CD36C/far-enable18CD369. Parser can longjmp on invalid token;no local positive/finite validation. Nominal return inherited from wrapper.
int __cdecl rf_console_wfar_command()
{
  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(16, 0);
    flt_663F34 = flt_180A400;
    sprintf(&unk_18CD828, "W far set to %d\n", (int)flt_180A400);
    rf_console_output_append_text_lines(&unk_18CD828, nullptr);
  }
  if ( dword_1809814 )
    rf_console_output_append_text_lines("Usage: wfar <float>\n", nullptr);
  return rf_renderer_rebuild_world_clip_planes_backend_wrapper();
}

