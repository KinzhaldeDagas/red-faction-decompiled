// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FAB50 rf_goal_register_shared_record_if_missing
// UNREALRED VERIFIED [mission-update-creation-continuation-20261027] Shared goal table registration: initial count0x90B050 must be<64 BEFORE name scan. Case-insensitive existing name returns unchanged; does not overwrite initial/current values. For new name increment count, select16-byte slot at0x90B0F0, assign string at+0, raw initial dword+8 and current+0xC. Full table returns without even deduplication scan. Save/restore lifetime not established by this registration body.
void __cdecl rf_goal_register_shared_record_if_missing(char *String2, int a2, int a3)
{
  char *v3; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  if ( dword_90B050 < 64 )
  {
    for ( i = 0; i < dword_90B050; ++i )
    {
      if ( rf_string_equals_case_insensitive((int)&byte_90B0F0[16 * i], String2) )
        return;
    }
    v3 = &byte_90B0F0[16 * dword_90B050++];
    rf_string_assign_from_cstr(v3, String2);
    *((_DWORD *)v3 + 2) = a2;
    *((_DWORD *)v3 + 3) = a3;
  }
}

