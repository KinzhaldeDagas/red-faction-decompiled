// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0058C090 rf_font_get_height_select_current
// UNREALRED VERIFIED [text-layout-20261029]: Argument signed font ID. Nonnegative selects global current-font pointer0x193BB9C=base0x193B688+108*ID WITHOUT upper bound. Negative selects default pointer0x193BBA0. Nonnull font returns DWORD+52 height;null returns16. Does not validate ID against font count or restore previous current font; unlike measure helper,nonnegative out-of-range IDs are not defaulted.
int __cdecl rf_font_get_height_select_current(int a1)
{
  if ( a1 >= 0 )
    unk_193BB9C = (char *)&unk_193B688 + 108 * a1;
  else
    unk_193BB9C = unk_193BBA0;
  if ( unk_193BB9C )
    return *(_DWORD *)(unk_193BB9C + 52);
  else
    return 16;
}

