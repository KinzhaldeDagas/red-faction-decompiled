// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047DB20 rf_rfl_read_section_header
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL header and prelude control flow, legacy light layouts, native ECX/stack arguments, environment initialization and multiplayer room tracking): 
// Cdecl(stream,section-id int32*out,section-size int32*out), AL Boolean. If signed position-at-or-past-end helper returns nonzero, fails without writing either output. Otherwise
// reads id(min0,default0). For stream version>=114, id0 is terminator: returns0 leaving size untouched. Older versions treat id0 as ordinary section. Calls
// progress_update_poll_network_and_callback(0,0) BEFORE reading size(min0,default0), then returns1. No section-id whitelist, nonnegative-size check, remaining-file bound, seek or
// read-error aggregation. Failed primitive read defaults can still produce success for nonterminating cases.
char __cdecl rf_rfl_read_section_header(_DWORD *a1, int *a2, int *a3)
{
  if ( rf_vfile_is_position_at_or_past_end_signed(a1) )
    return 0;
  *a2 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  if ( rf_vfile_get_slot_version(a1) >= 114 && !*a2 )
    return 0;
  rf_progress_update_poll_network_and_callback(0, 0);
  *a3 = rf_binary_stream_read_int32_versioned(a1, 0, 0);
  return 1;
}

