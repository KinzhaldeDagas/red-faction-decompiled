// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00419A30 rf_glare_definition_names_clear_shutdown
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): For signed i=0 while i<globalCount0x680AE0, assigns empty C string0x63177F into RFString at0x680DD8+52*i. No64-entry clamp, count reset, bitmap release, scalar clearing, runtime-list destruction or outer table free. This atexit hook clears names only.
void __cdecl rf_glare_definition_names_clear_shutdown()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < dword_680AE0; ++i )
    rf_string_assign_from_cstr(&byte_680DD8[52 * i], (char *)&byte_63177F);
}

