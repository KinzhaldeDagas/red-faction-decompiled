// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BB850 rf_text_file_open_write
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Closes prior state only if FILE*+0 nonNULL. Opens binary append ab for ANY nonzero append byte, otherwise wb/truncate. Open failure returns1. Success setvbuf(FILE,NULL,0,requestedSize), ignores return, clears flags+24 mask0x2/read-mode flag and returns0. No read-buffer allocation or reset of cursor/count/EOF/newline bits. Constructor initializes only FILE*/buffer pointers.
int __thiscall rf_text_file_open_write(void *this, const char *FileName, unsigned __int8 a3, unsigned int Size)
{
  char *Mode; // [esp+0h] [ebp-8h]

  if ( *(_DWORD *)this )
    rf_text_file_close_and_reset_handles((int)this);
  if ( a3 )
    Mode = "ab";
  else
    Mode = "wb";
  *(_DWORD *)this = fopen(FileName, Mode);
  if ( !*(_DWORD *)this )
    return 1;
  setvbuf(*(FILE **)this, nullptr, 0, Size);
  *((_DWORD *)this + 6) &= ~2u;
  return 0;
}

