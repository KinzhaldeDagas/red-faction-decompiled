// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058C020 rf_text_byte_is_space_tab_lf
// UNREALRED VERIFIED [text-layout-20261029]: Returns boolean true ONLY for byte space32,tab9 or LF10. CR13 and other CRT whitespace returnfalse. No locale lookup or mutation.
BOOL __cdecl rf_text_byte_is_space_tab_lf(char a1)
{
  return a1 == 32 || a1 == 9 || a1 == 10;
}

