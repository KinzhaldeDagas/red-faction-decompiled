// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060C988 _fscanf
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Public variadic fscanf adapter. LEA address of caller vararg area at EBP+16, push argsPtr,NULL locale,original Format,original Stream, then input_l CALLBACK
// ADDRESS; cdecl CALL60C87E internal five-slot scanner dispatcher, ADD20. No FILE/format/vararg dereference, validation, locale snapshot or scanning in wrapper. Old three-argument
// vfscanf type shifted every argument; corrected dispatcher ABI proves actual mapping and fixes caller pseudocode. Caller retains all original variadic slots.
int fscanf(FILE *const Stream, const char *const Format, ...)
{
  va_list arguments; // [esp+10h] [ebp+10h] BYREF

  va_start(arguments, Format);
  return vfscanf((int (__cdecl *)(void *, const char *, void *, char *))_input_l, Stream, Format, nullptr, arguments);
}

