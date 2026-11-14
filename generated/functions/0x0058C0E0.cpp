// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058C0E0 rf_font_get_spacing_select_current
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, glyph/string layouts, read/write flow and callers): Nonnegative font ID selects current record=base+108*ID without upper-bound check; negative selects default pointer193BBA0. Returns record DWORD+56, or16 if selected pointer NULL. Font loader initializes+56 from height+52; load wrapper can override it. This getter mutates current-font global and does not restore prior selection.
int __cdecl rf_font_get_spacing_select_current(int a1)
{
  if ( a1 >= 0 )
    unk_193BB9C = (char *)&unk_193B688 + 108 * a1;
  else
    unk_193BB9C = unk_193BBA0;
  if ( unk_193BB9C )
    return *(_DWORD *)(unk_193BB9C + 56);
  else
    return 16;
}

