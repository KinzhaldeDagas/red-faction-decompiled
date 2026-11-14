// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005787B0 rf_text_parser_open_file_or_fatal
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, parser cursor/CR rules, bookmark restoration, prefix/delimiter matching, integer hex-loop and CRT terminator semantics): ECX receiver plus(path,context),RET8. Calls578EA0 owned-buffer file open with third stack argument0;negative result formats Unable to open parse file and invokes fatal parse.cpp209. Otherwise returns receiver. Does not run empty constructor,close existing buffer,check full read or add filename bounds;inherits open ownership/cache quirks.256B diagnostic buffer receives unbounded sprintf.
void *__thiscall rf_text_parser_open_file_or_fatal(void *self, const char *path, void *context)
{
  char Buffer[256]; // [esp+4h] [ebp-108h] BYREF
  int v6; // [esp+108h] [ebp-4h]

  v6 = rf_memory_text_parser_open_file_to_owned_buffer(self, path, context, 0);
  if ( v6 < 0 )
  {
    sprintf(Buffer, "Unable to open parse file %s", path);
    rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\parse\\parse.cpp", 209, Buffer);
  }
  return self;
}

