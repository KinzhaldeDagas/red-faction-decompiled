// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A83A _calloc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(count,width), pointer result. Initialize local
// status0 and call calloc_impl(count,width,&status). If result nonNULL OR status0, return result without own errno write. Otherwise call errno(), test pointer nonNULL; if nonNULL
// call errno() AGAIN and store local status through second returned pointer, then return savedNULL result. No own invalid-parameter call, multiplication or zeroing. Implementation
// writes optional status12 only for allocation exhaustion; overflow implementation directly sets errno/handler and leaves this status0. Does not clear previous errno on success or
// free an allocation.
void *__cdecl calloc(size_t Count, size_t Size)
{
  void *v2; // esi
  int v4; // [esp+4h] [ebp-4h] BYREF

  v4 = 0;
  v2 = _calloc_impl(Count, Size, &v4);
  if ( !v2 && v4 && _errno() )
    *_errno() = v4;
  return v2;
}

