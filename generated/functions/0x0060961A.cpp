// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060961A __get_printf_count_output
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Return canonical integer1 iff global202134C equals (securityCookieDWORD664BD8 OR1),else0. Reads both globals, no write/encoding/callback. This
// checks cookie-derived stored enable token; not simply global!=0 and no printf execution.
int __cdecl _get_printf_count_output()
{
  return unk_202134C == (dword_664BD8 | 1);
}

