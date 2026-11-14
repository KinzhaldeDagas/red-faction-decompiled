// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006085CF _fclose
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Public fclose. NULL ->invalid/-1. flags&0x40 synthetic-string stream:
// simply flags0,return-1,NO lock/flush/close/free. Otherwise lock_file,armSEH,callfclose_nolock,saveresult,normal/abnormal finally unlock_file,return savedresult. No FILEallocation
// free in this wrapper; closing dynamic FILE storage is separate fcloseall policy. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return
// only if handler returns. Explicit errno34 or no-handler paths retain their separately described policy.
int __cdecl fclose(FILE *Stream)
{
  int v2; // [esp+10h] [ebp-1Ch]

  v2 = -1;
  if ( Stream )
  {
    if ( (Stream->_flag & 0x40) != 0 )
    {
      Stream->_flag = 0;
    }
    else
    {
      _lock_file(Stream);
      v2 = _fclose_nolock(Stream);
      _unlock_file(Stream);
    }
    return v2;
  }
  else
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return -1;
  }
}

