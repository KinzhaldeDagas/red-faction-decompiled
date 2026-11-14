// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004797C0 rf_level_verification_optional_reports
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): No arguments consumed. If DWORD1809818 nonzero, calls solid texture-usage statistics478A40(worldSolid). Then independently if shared
// console helpDWORD1809814 nonzero, constructs temporary RFString from literal Usage: verify_level followed by newline, appends console text with second argumentNULL, destroys
// temporary with SEH cleanup. Texture reporting precedes help; help does not suppress it. Neither flag set ->no report. No full level-validation traversal, return-status aggregation
// or locale registration. This is application code falsely named/flagged std::locale::facet::facet_Register; no direct entry xrefs were present in inspected IDB.
void __cdecl rf_level_verification_optional_reports()
{
  const char *v0; // eax
  std::exception *v1; // [esp+4h] [ebp-1Ch]
  _DWORD v2[2]; // [esp+Ch] [ebp-14h] BYREF
  int v3; // [esp+1Ch] [ebp-4h]

  if ( dword_1809818 )
    rf_solid_report_texture_usage_statistics(rf_world_solid);
  if ( dword_1809814 )
  {
    v1 = (std::exception *)rf_string_construct_from_cstr(v2, "Usage: verify_level\n");
    v3 = 0;
    v0 = rf_string_object_c_str_or_empty(v1);
    rf_console_output_append_text_lines(v0, nullptr);
    v3 = -1;
    rf_string_destroy_buffer(v2);
  }
}

