// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00561700 rf_text_log_buffer_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, relative timestamp serialization, RFString extent/buffer ownership, bounded text-log branches and tagged model lookups): Constructs24byte record:pointer0,external-storage byte4,capacity8,used12,maxLines16,lineCount20. Lazily caches minimum allocation=strlen(global marker"Buffer overrun!")+2. Supplied external pointer is retained with byte4=1 and capacity left exactly as caller supplied; otherwise allocates max(requestedSize,minimum) with byte4=0. Sets maxLines and clears buffer via561800 (writes byte0NUL,used0,lineCount1). No null/negative external-capacity validation; remaining padding untouched.
_BYTE *__thiscall rf_text_log_buffer_construct(_BYTE *this, int a2, int Size, int a4)
{
  if ( dword_663E9C < 1 )
    dword_663E9C = strlen(off_663E98) + 2;
  if ( a2 )
  {
    *(this + 4) = 1;
    *(_DWORD *)this = a2;
  }
  else
  {
    *(this + 4) = 0;
    if ( Size < dword_663E9C )
      Size = dword_663E9C;
    *(_DWORD *)this = operator new(Size);
  }
  *((_DWORD *)this + 2) = Size;
  *((_DWORD *)this + 4) = a4;
  rf_text_log_buffer_clear(this);
  return this;
}

