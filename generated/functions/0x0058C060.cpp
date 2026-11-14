// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058C060 rf_text_byte_is_space_or_tab
// UNREALRED VERIFIED [text-layout-20261029]: Returns true ONLY for space32 or tab9. Used to skip wrap separators; LF handled separately,CR not skipped. No locale dependency.
BOOL __cdecl rf_text_byte_is_space_or_tab(char a1)
{
  return a1 == 32 || a1 == 9;
}

