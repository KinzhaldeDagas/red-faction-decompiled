// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BB780 rf_text_file_open_read
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): If FILE*+0 already nonNULL, calls close/reset5BBBC0. Clears flags+24 mask0x1 (EOF/short-read latch), fopen(path,rb); failure returns1. Calls setvbuf(FILE,NULL,4,0), ignores result. Stores capacity+20, mallocs buffer+4, initializes remaining+16=0, invokes refill-and-newline-detection5BB8E0. Nonzero detection status closes state; then ORs flags mask0x2 even on that hypothetical failure. Allocation failure closes/reset and returns1; success returns0. No capacity>0 check; constructor did not initialize flag bits. Existing nonNULL buffer with NULL FILE* is not independently closed before allocation.
int __thiscall rf_text_file_open_read(void *this, const char *FileName, unsigned int Size)
{
  int v5; // [esp+4h] [ebp-4h]

  if ( *(_DWORD *)this )
    rf_text_file_close_and_reset_handles((int)this);
  *((_DWORD *)this + 6) &= ~1u;
  *(_DWORD *)this = fopen(FileName, "rb");
  if ( !*(_DWORD *)this )
    return 1;
  setvbuf(*(FILE **)this, nullptr, 4, 0);
  *((_DWORD *)this + 5) = Size;
  *((_DWORD *)this + 1) = malloc(Size);
  if ( *((_DWORD *)this + 1) )
  {
    *((_DWORD *)this + 4) = 0;
    v5 = rf_text_file_refill_and_detect_newlines((int)this);
    if ( v5 )
      rf_text_file_close_and_reset_handles((int)this);
    *((_DWORD *)this + 6) |= 2u;
    return v5;
  }
  else
  {
    rf_text_file_close_and_reset_handles((int)this);
    return 1;
  }
}

