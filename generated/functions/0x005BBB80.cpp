// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BBB80 rf_text_file_destroy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Closes nonNULL FILE*+0 and CRT-frees nonNULL read buffer+4. Does NOT clear either pointer or other object state. Does not delete containing28-byte object; scalar deleting destructor490340 handles that. Repeated destructor call on retained object can reuse stale handles/pointers.
void __thiscall rf_text_file_destroy(int this)
{
  if ( *(_DWORD *)this )
    fclose(*(FILE **)this);
  if ( *(_DWORD *)(this + 4) )
    free(*(void **)(this + 4));
}

