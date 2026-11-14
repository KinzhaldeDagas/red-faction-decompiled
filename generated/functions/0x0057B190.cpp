// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B190 rf_text_parser_is_cursor_at_nul
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): ECX parser. Returns BOOL32 equal to byte at cursor field4 being zero. Does not skip whitespace/comments or compare cursor against buffer bounds/size268; no null cursor guard.
BOOL __thiscall rf_text_parser_is_cursor_at_nul(char **this)
{
  return **(this + 1) == 0;
}

