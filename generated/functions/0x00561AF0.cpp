// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561AF0 rf_text_log_buffer_append_printf_unbounded
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): cdecl(record,format,...). Uses vsprintf into fixed1024byte STACK buffer with no bound, then appends resulting C string through561860. Large formatted output can overrun temporary before destination capacity handling. Standard variadic format, not RF custom vector formatter; returns append helper mixed bits.
char *rf_text_log_buffer_append_printf_unbounded(const char **a1, char *Format, ...)
{
  char Buffer[1024]; // [esp+0h] [ebp-408h] BYREF
  va_list ArgList; // [esp+404h] [ebp-4h]
  va_list va; // [esp+418h] [ebp+10h] BYREF

  va_start(va, Format);
  va_copy(ArgList, va);
  vsprintf(Buffer, Format, va);
  ArgList = nullptr;
  return rf_text_log_buffer_append_cstr(a1, Buffer);
}

