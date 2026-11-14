// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608BD1 _fseek
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Public fseek. Require nonNULLstream and origin EXACT0,1
// or2,elseinvalid/-1 beforelock. Lock_file/armSEH/forward to fseek_nolock/save result/finallyunlock on normalorunwind. No own offsetrange, filelength, flushresult or positionrollback
// policy. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or no-handler paths retain
// their separately described policy.
int __cdecl fseek(FILE *Stream, int Offset, int Origin)
{
  int v4; // [esp+10h] [ebp-1Ch]

  if ( Stream && (unsigned int)Origin <= 2 )
  {
    _lock_file(Stream);
    v4 = _fseek_nolock(Stream, Offset, Origin);
    _unlock_file(Stream);
    return v4;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

