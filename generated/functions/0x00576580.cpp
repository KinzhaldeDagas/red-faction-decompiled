// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00576580 rf_bitmap_resolved_format_is_4_5_7
// UNREALRED VERIFIED [lightmap-shadows-20261028]: Calls0x576550 and returnstrue exactlyfor internalformatcodes4,7,5; falsefor allothers. Shadowprojector0x550950 excludesfaces withbitmap satisfyingthispredicate. No bitmaphandlevalidation beyondcallee; no pixeldata scan oralphatest inbody.
bool __cdecl rf_bitmap_resolved_format_is_4_5_7(unsigned int a1)
{
  int resolved_format_code; // [esp+4h] [ebp-4h]

  resolved_format_code = rf_bitmap_get_resolved_format_code(a1);
  return resolved_format_code == 4 || resolved_format_code == 7 || resolved_format_code == 5;
}

