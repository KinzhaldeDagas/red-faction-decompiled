// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00507C80 rf_ammo_clear_record_strings
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Loops signed indices0..<911480, stride20 at911488, assigns BOTH RFStrings+0/+8 from distinct original-PE NUL literals63E66B/63E689. Does not reset ammo count, clear bitmap handle+16, explicitly unload bitmaps or free registry array. Registered by507AD0 as exit cleanup; uses RFString assignment, not whole-record destructor.
void __cdecl rf_ammo_clear_record_strings()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < unk_911480; ++i )
  {
    rf_string_assign_from_cstr((_DWORD *)&unk_911488 + 5 * i, (char *)&byte_63E66B);
    rf_string_assign_from_cstr((_DWORD *)&unk_911490 + 5 * i, (char *)byte_63E689);
  }
}

