// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061D85C __recalloc
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Invalid(E) here means storing errno E, invoking
// invalid_parameter(NULL,NULL,NULL,0,0), and returning the stated status only if the handler returns. Cdecl(block,count,width), returns reallocated pointer/NULL. Nonzero count
// requires width<=0xFFFFFFE0/count; overflow ->invalid(12)/NULL before querying or freeing block. Compute total product; oldSize0 when blockNULL, else msize(block) used RAW without
// checkingUINT_MAX failure. Call realloc(block,total); if nonNULL AND unsigned oldSize<total, memset exactly newPointer+oldSize through requested total to0, ignore fill result. No
// zeroing below old allocated capacity or beyond requested total, no reset on shrink; msize failure UINT_MAX suppresses zero-fill while still attempting realloc. Total0/blocknonNULL
// delegates free via realloc; total0/blockNULL can allocate minimal uninitialized padding through malloc. No separate ownership/extent validation or rollback after successful
// realloc.
void *__cdecl _recalloc(void *Block, size_t Count, size_t Size)
{
  size_t v3; // ebx
  size_t v5; // esi
  char *v6; // eax
  void *v7; // edi

  v3 = 0;
  if ( Count && 0xFFFFFFE0 / Count < Size )
  {
    *_errno() = 12;
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return nullptr;
  }
  else
  {
    v5 = Size * Count;
    if ( Block )
      v3 = _msize(Block);
    v6 = (char *)realloc(Block, v5);
    v7 = v6;
    if ( v6 )
    {
      if ( v3 < v5 )
        memset(&v6[v3], 0, v5 - v3);
    }
    return v7;
  }
}

