// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00621BFD __strnicmp
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid22 means errno22 plus
// invalid_parameter(NULL,NULL,NULL,0,0); stated status/cleanup follows only if the handler returns. Cdecl(first,second,unsigned count). LIVE2021B8C nonzero forwards
// strnicmp_l(first,second,count,NULLlocale); that delegate returns0 for count0 BEFORE validating pointers. Global0 branch instead checks BOTH pointers nonNULL and count<=INT_MAX even
// for count0; failure ->Invalid22/INT_MAX. Valid fast path restores ESI/EBP and tail-jumps ascii_strnicmp622080, returning normalized -1/0/+1 (count0 ->0 with no string read).
// Therefore NULL-string/count0 behavior depends on global branch, do not apply an unconditional zero-count shortcut to this wrapper. No own locale object, string write or count
// multiplication.
int __cdecl _strnicmp(const char *String1, const char *String2, size_t MaxCount)
{
  if ( unk_2021B8C )
    return _strnicmp_l(String1, String2, MaxCount, nullptr);
  if ( String1 && String2 && MaxCount <= 0x7FFFFFFF )
    return __ascii_strnicmp((unsigned __int8 *)String1, (unsigned __int8 *)String2, MaxCount);
  *_errno() = 22;
  _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
  return 0x7FFFFFFF;
}

