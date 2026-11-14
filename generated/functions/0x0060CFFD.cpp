// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CFFD _sscanf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Variadic sscanf wrapper. Save caller ESI; move source string from caller slot0 into ESI, LEA vararg area EBP+16. Push four slots in reverse to call60CF93
// vscan_fn: input_l callback,format,NULL locale,argsPtr, with source separately in ESI. ADD16,restoreESI/frame,return helperEAX. No direct string scan/NULL check/copy, destination
// capacity validation or stdio lock. Source is NOT an additional fifth stack slot; corrected pointer/count callback ABI retains original variadic arguments.
int sscanf(const char *const Buffer, const char *const Format, ...)
{
  va_list arguments; // [esp+14h] [ebp+10h] BYREF

  va_start(arguments, Format);
  return vscan_fn(Buffer, (int (__cdecl *)(void *, const char *, void *, char *))_input_l, Format, nullptr, arguments);
}

