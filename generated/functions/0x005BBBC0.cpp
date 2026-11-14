// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BBBC0 rf_text_file_close_and_reset_handles
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): If FILE*+0 nonNULL calls fclose then sets pointerNULL; if read-buffer+4 nonNULL calls free thenNULL. Leaves end/cursor/count/capacity/flags unchanged; does not delete containing object or report fclose errors. Distinct from destructor5BBB80, which leaves pointers unchanged.
void __thiscall rf_text_file_close_and_reset_handles(int this)
{
  if ( *(_DWORD *)this )
  {
    fclose(*(FILE **)this);
    *(_DWORD *)this = 0;
  }
  if ( *(_DWORD *)(this + 4) )
  {
    free(*(void **)(this + 4));
    *(_DWORD *)(this + 4) = 0;
  }
}

