// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613D24 __stricmp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid22 means errno22 plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated status/cleanup follows only if the handler returns. Cdecl(first,second). LIVE2021B8C nonzero forwards
// stricmp_l(first,second,NULLlocale), without own pointer validation. Global0 validates both nonNULL, otherwiseInvalid22/INT_MAX; valid path restores ESI/EBP and tail-jumps
// ascii_stricmp613C16, preserving original stack arguments. ASCII helper folds only A..Z and returns exact folded byte difference. No string mutation, count bound or locale
// construction in fast path.
int __cdecl _stricmp(const char *String1, const char *String2)
{
  if ( unk_2021B8C )
    return _stricmp_l(String1, String2, nullptr);
  if ( String1 && String2 )
    return __ascii_stricmp((unsigned __int8 *)String1, (unsigned __int8 *)String2);
  *_errno() = 22;
  _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
  return 0x7FFFFFFF;
}

