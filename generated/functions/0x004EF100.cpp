// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF100 rf_undercover_clear_profile_strings_at_exit
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): Atexit callback registered by undercover profile initializer. Assigns empty C string at63D1B0 to RFString87FC28, then empty string63D1B1 to twelve RFStrings87FC34+8*i (i0..11, last87FC8C). These are assignment calls, not string destructor calls. Leaves other profile IDs, mode flags, timestamps, models and textures untouched.
void __cdecl rf_undercover_clear_profile_strings_at_exit()
{
  int i; // [esp+0h] [ebp-4h]

  rf_string_assign_from_cstr(unk_87FC28, (char *)&byte_63D1B0);
  for ( i = 0; i < 12; ++i )
    rf_string_assign_from_cstr((_DWORD *)(8 * i + 8911924), (char *)byte_63D1B1);
}

