// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005737D0 rf_console_screen_res_command
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, clipping arithmetic, stack ABI and callers): Recovered no-argument console callback. Execution flag1809818 triggers two required numeric parses(type8) for width/height and optional parse(type9) for bpp, defaulting to current bpp. Optional-value presence uses1809308 bit8. Prints request, calls cached screen-dimensions setter, and prints success/failed. Independent help flag1809814 prints usage. No direct device reset, range validation or filesystem change.
void __cdecl rf_console_screen_res_command()
{
  int v0; // [esp+0h] [ebp-Ch]
  int v1; // [esp+4h] [ebp-8h]
  int v2; // [esp+8h] [ebp-4h]

  if ( dword_1809818 )
  {
    rf_console_read_argument_validate_type_mask(8, 0);
    v2 = dword_180981C;
    rf_console_read_argument_validate_type_mask(8, 0);
    v1 = dword_180981C;
    v0 = dword_187CCB0;
    rf_console_read_argument_validate_type_mask(9, 0);
    if ( (dword_1809308 & 8) != 0 )
      v0 = dword_180981C;
    sprintf(&unk_18CD828, "Setting screen_res to %dx%d, %d bits per pixel\n", v2, v1, v0);
    rf_console_output_append_text_lines(&unk_18CD828, nullptr);
    if ( rf_renderer_set_cached_screen_dimensions(v2, v1, v0) )
      rf_console_output_append_text_lines("success!\n", nullptr);
    else
      rf_console_output_append_text_lines("failed.\n", nullptr);
  }
  if ( dword_1809814 )
    rf_console_output_append_text_lines("Usage: screen_res w h [bits per pixel]\n", nullptr);
}

