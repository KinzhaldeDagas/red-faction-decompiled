// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056E930 rf_console_history_save_if_enabled
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): No args. Constructs local VFile even when save disabled. If byte663EE0==0 or open console_history file with write flag2 fails,destroys local and returns incidental destructor result. Otherwise writes signed LAST occupied history index663EE4 as host int32,then inclusive slots0..last via stream5A08B0 u16-length/no-NUL strings with length-1. Thus last7 means8 strings,last-1 meansnone. Closes/destroys file;no per-write error handling or own index clamp. Read-side load is not gated by this save flag.
int __cdecl rf_console_history_save_if_enabled()
{
  int stream[70]; // [esp+4h] [ebp-12Ch] BYREF
  int i; // [esp+120h] [ebp-10h]
  int v3; // [esp+12Ch] [ebp-4h]

  rf_vfile_construct_unopened(stream);
  v3 = 0;
  if ( !byte_663EE0 || rf_vfile_open_with_extension_cache_control_paths(stream, aConsoleHistory, 2, byte_98967F) )
  {
    v3 = -1;
    return rf_vfile_destruct_close_if_open(stream);
  }
  else
  {
    rf_binary_stream_write_int32_host_order(stream, dword_663EE4);
    for ( i = 0; i <= dword_663EE4; ++i )
      rf_binary_stream_write_u16_length_string(stream, &unk_1809AC0[256 * i], -1);
    rf_vfile_close_stdio_or_vpp(stream);
    v3 = -1;
    return rf_vfile_destruct_close_if_open(stream);
  }
}

