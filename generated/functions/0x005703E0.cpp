// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005703E0 rf_console_history_load_clamped_last_index
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Constructs local VFile;opens console history with read flag1 even when save-history flag disabled. Failure only destroys local,preserving previous last-index. Success reads signed int32 last occupied index663EE4 and clamps to[0,7],then reads slots0..last inclusive withu16-length reader and capacity-1 (no256B bound). Empty saved index-1 therefore clamps0 and attempts one string read. Corrupt long string can overrun slot;read errors not individually checked. Closes/destroys local and returns destructor incidental result.
int __cdecl rf_console_history_load_clamped_last_index()
{
  int self[70]; // [esp+4h] [ebp-12Ch] BYREF
  int i; // [esp+120h] [ebp-10h]
  int v3; // [esp+12Ch] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v3 = 0;
  if ( rf_vfile_open_with_extension_cache_control_paths(self, aConsoleHistory, 1, byte_98967F) )
  {
    v3 = -1;
    return rf_vfile_destruct_close_if_open(self);
  }
  else
  {
    dword_663EE4 = rf_binary_stream_read_int32_versioned(self, 0, 0);
    rf_integer_clamp_in_place(&dword_663EE4, 0, 7);
    for ( i = 0; i <= dword_663EE4; ++i )
      rf_binary_stream_read_u16_string_to_buffer(self, &unk_1809AC0[256 * i], -1, 0, nullptr);
    rf_vfile_close_stdio_or_vpp(self);
    v3 = -1;
    return rf_vfile_destruct_close_if_open(self);
  }
}

