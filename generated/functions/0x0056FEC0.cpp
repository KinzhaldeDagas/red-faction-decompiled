// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056FEC0 rf_console_lexer_set_ascii_casefold
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): cdecl(int flag). Stores raw32bit flag663F00 and returns it unchanged. Normalizer uses nonzero to add32 to ASCII uppercase;no canonical boolean conversion or lexer reset.
int __cdecl rf_console_lexer_set_ascii_casefold(int a1)
{
  dword_663F00 = a1;
  return a1;
}

