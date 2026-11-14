// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044CE20 rf_hud_personas_clear_strings
// UNREALRED VERIFIED [persona-lifecycle-20260923]: Iterates the stored persona count, clears name/display-name/image strings and writes zero at message-text +0x24. This routine does not stop voice handles or release bitmap handles in the shown body; do not label it complete audio/resource teardown.
void __cdecl rf_hud_personas_clear_strings()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_hud_persona_count; ++i )
  {
    rf_string_assign_from_cstr(&rf_hud_persona_records[296 * i], (char *)&byte_63448C);
    rf_string_assign_from_cstr((_DWORD *)&unk_6EF1B0 + 74 * i, (char *)&byte_63448D);
    rf_string_assign_from_cstr((_DWORD *)&unk_6EF1A8 + 74 * i, (char *)&byte_63448E);
    unk_6EF1C4[296 * i] = 0;
  }
}

