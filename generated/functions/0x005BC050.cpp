// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BC050 rf_text_file_printf
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Cdecl variadic(receiver,format,...). Uses UNBOUNDED vsprintf into1024-byte stack buffer,then forwards to normalized-newline writer5BBE70. Returns writer0/1 status; ignores vsprintf length/error. Format output longer than buffer can exceed local storage. No automatic trailing newline,flush or FILE* validation.
BOOL rf_text_file_printf(FILE **a1, char *Format, ...)
{
  char Buffer[1024]; // [esp+0h] [ebp-408h] BYREF
  va_list ArgList; // [esp+404h] [ebp-4h]
  va_list va; // [esp+418h] [ebp+10h] BYREF

  va_start(va, Format);
  va_copy(ArgList, va);
  vsprintf(Buffer, Format, va);
  ArgList = nullptr;
  return rf_text_file_write_normalized_newlines(a1, Buffer);
}

