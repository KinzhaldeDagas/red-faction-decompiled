// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608AD9 _ftell
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Public ftell. NULL ->invalid/-1;else
// lock_file,armSEH,callftell_nolock,saveintresult,finally unlock_file on normal/unwind,return savedresult. No own position math, buffer/header repair or exception catch converting
// failures to status. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or no-handler paths
// retain their separately described policy.
int __cdecl ftell(FILE *Stream)
{
  int v2; // [esp+10h] [ebp-1Ch]

  if ( Stream )
  {
    _lock_file(Stream);
    v2 = _ftell_nolock(Stream);
    _unlock_file(Stream);
    return v2;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

