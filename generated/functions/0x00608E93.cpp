// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608E93 _fwrite
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Public fwrite. size0/count0 ->0 before stream/bufferchecks. NULLstream
// ->invalid/0. Otherwise lock_file,armSEH,forwardfour slots to fwrite_nolock,save result,normal/abnormal finallyunlock. Buffer/product validation delegated afterlock; no
// partial-buffer wipe or own write retry. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34
// or no-handler paths retain their separately described policy.
size_t __cdecl fwrite(const void *Buffer, size_t ElementSize, size_t ElementCount, FILE *Stream)
{
  size_t v5; // [esp+10h] [ebp-1Ch]

  if ( !ElementSize || !ElementCount )
    return 0;
  if ( !Stream )
  {
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 0;
  }
  _lock_file(Stream);
  v5 = _fwrite_nolock(Buffer, ElementSize, ElementCount, Stream);
  _unlock_file(Stream);
  return v5;
}

