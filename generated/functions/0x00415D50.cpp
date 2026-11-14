// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00415D50 rf_clutter_model_kind_for_first_filename_match
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Cdecl CString filename. Scans signed class indices0..<globalcount666B60;case-insensitive full RFString filename8 match returns FIRST matching classDWORD56(modelkind). Returns0 onmiss (also possible storedkind0). No filename normalization/path stripping,duplicate/index-capacity/NULL guard or mutation;does not return classindex or modelhandle.
int __cdecl rf_clutter_model_kind_for_first_filename_match(char *String2)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_666B60; ++i )
  {
    if ( rf_string_equals_case_insensitive((int)&unk_667008 + 232 * i, String2) )
      return dword_667038[58 * i];
  }
  return 0;
}

