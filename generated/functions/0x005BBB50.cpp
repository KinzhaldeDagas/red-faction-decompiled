// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BBB50 rf_text_file_construct
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Constructor for28-byte text-file object used by factories. Clears only FILE* at+0 and owned read-buffer pointer+4; returns receiver. Leaves buffer end+8,cursor+12,remaining+16,capacity+20,flags+24 untouched. Generic runtime name replaced based on both allocation callers; no allocation or stream open occurs here.
_DWORD *__thiscall rf_text_file_construct(_DWORD *this)
{
  *this = 0;
  *(this + 1) = 0;
  return this;
}

