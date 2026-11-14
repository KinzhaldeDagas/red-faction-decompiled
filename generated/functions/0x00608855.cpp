// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00608855 _fread_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native32-bit FILE offsets: ptr0,cnt4,base8,flags12,fd16,charbuf20,bufsiz24,tmpname28. Public fread_s. size0/count0 ->0 before any pointervalidation.
// NULLstream: if capacity!=UINT_MAX callmemset(buffer,0,capacity) BEFORE invalid/0; buffer not independently validated here. NonNULLstream:lock_file,armSEH,forward allfive slots to
// fread_nolock_s,saveresult,normal/abnormal finally unlock. Returns saved element count; buffer/product/capacity validation and clearing delegated. No independent capacity discovery
// or state rollback. Unqualified invalid denotes errno22 plus invalid_parameter(NULL,NULL,NULL,0,0), with stated return only if handler returns. Explicit errno34 or no-handler paths
// retain their separately described policy.
size_t __cdecl fread_s(void *Buffer, size_t BufferSize, size_t ElementSize, size_t ElementCount, FILE *Stream)
{
  size_t v6; // [esp+10h] [ebp-1Ch]

  if ( !ElementSize || !ElementCount )
    return 0;
  if ( !Stream )
  {
    if ( BufferSize != -1 )
      memset(Buffer, 0, BufferSize);
    *_errno() = 22;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return 0;
  }
  _lock_file(Stream);
  v6 = _fread_nolock_s(Buffer, BufferSize, ElementSize, ElementCount, Stream);
  _unlock_file(Stream);
  return v6;
}

