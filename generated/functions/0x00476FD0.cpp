// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476FD0 rf_console_show_level_info
// UNREALRED VERIFIED [cutscene-playback-20261028]: CORRECTION to false library signature: executable body is level-info console command, not std::locale::facet::facet_Register. Help flag0x1809814 prints Shows info on the current level; otherwise constructs Filename: + current logical level RF string0x6FC31C, prints it through0x56DD50 and destroys temporary RF string. No locale/facet registration behavior.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, item/cutscene/HUD caller chains, original float constants, RFString ownership and false SDK classifications
// and native signed/x87/stack/callback ABI): Fresh native verification confirms application console handler despite remaining FUNC_LIB flag, which is cleared. No arguments.
// HelpDWORD1809814 nonzero prints Shows info on the current level with NULL second console argument; else concatenates Filename: prefix and current RFString6FC31C into owned
// temporary, prints, destroys including SEH. Existing already-correct void prototype/name retained. No locale/facet registration, level loading or level validation here.
void __cdecl rf_console_show_level_info()
{
  const char *v0; // eax
  std::exception *v1; // [esp+4h] [ebp-1Ch]
  _BYTE v2[8]; // [esp+Ch] [ebp-14h] BYREF
  int v3; // [esp+1Ch] [ebp-4h]

  if ( dword_1809814 )
  {
    rf_console_output_append_text_lines("Shows info on the current level", nullptr);
  }
  else
  {
    v1 = (std::exception *)rf_string_concat_cstr_object(v2, "Filename: ", (const void **)unk_6FC31C);
    v3 = 0;
    v0 = rf_string_object_c_str_or_empty(v1);
    rf_console_output_append_text_lines(v0, nullptr);
    v3 = -1;
    rf_string_destroy_buffer(v2);
  }
}

