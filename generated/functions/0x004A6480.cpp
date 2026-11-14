// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6480 rf_multiplayer_log_printf
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Cdecl variadic(format,...), no fixed extra floating argument. If FILE7B1530 nonnull, unbounded vsprintf formats into1024-byte stack buffer, then log_write_line(buffer, timestamp1);
// no own format-null/output-size bound. Disabled FILE returns before va formatting. Does not open file or report I/O status. The writer subsequently also passes composed message as
// printf format; no percent escaping here.
void rf_multiplayer_log_printf(char *Format, ...)
{
  char Buffer[1024]; // [esp+0h] [ebp-408h] BYREF
  va_list ArgList; // [esp+404h] [ebp-4h]
  va_list va; // [esp+414h] [ebp+Ch] BYREF

  va_start(va, Format);
  if ( MEMORY[0x7B1530] )
  {
    va_copy(ArgList, va);
    vsprintf(Buffer, Format, va);
    ArgList = nullptr;
    rf_multiplayer_log_write_line(Buffer, 1);
  }
}

