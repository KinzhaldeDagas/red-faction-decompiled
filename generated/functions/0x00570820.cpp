// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570820 rf_console_printf_unbounded_stack2048
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl(format,...). Zeroes2048B stack buffer,formats with unbounded vsprintf,then appends through56DD50 with default color. Does not enforce2048B formatting bound or per-ring-line257B bound;no automatic newline. EAX is output helper incidental value,not formatted length or success.
int rf_console_printf_unbounded_stack2048(char *Format, ...)
{
  char Buffer[2048]; // [esp+0h] [ebp-808h] BYREF
  va_list ArgList; // [esp+804h] [ebp-4h]
  va_list va; // [esp+814h] [ebp+Ch] BYREF

  va_start(va, Format);
  memset(Buffer, 0, sizeof(Buffer));
  va_copy(ArgList, va);
  vsprintf(Buffer, Format, va);
  ArgList = nullptr;
  return rf_console_output_append_text_lines(Buffer, nullptr);
}

