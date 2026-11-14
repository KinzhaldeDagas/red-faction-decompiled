// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CA10 rf_cstring_find_last_char_wrapper
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl(Str,ch), two DWORD slots. Pushes ch then Str to distinct CRT _strrchr at606C10, removes8 outgoing bytes and forwards EAX; no null guard or additional
// string scan. Library-wrapper name now distinguishes it from its callee so pseudocode no longer appears recursively self-calling. Character normalization, terminating-NUL search and
// match/failure semantics are the underlying CRT callee responsibility; generic wrapper retains library classification.
char *__cdecl rf_cstring_find_last_char_wrapper(char *Str, int a2)
{
  return strrchr(Str, a2);
}

