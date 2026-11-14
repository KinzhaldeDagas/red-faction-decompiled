// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B7D80 rf_object_delete_unprotected_slots_and_reset_counter
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): No arguments. Scans signed indices0..1023 of object table7B7E10 once in ascending order; deletes each currently nonnull object through4B73B0 only
// when common DWORD+124 bit0x800 is clear. Protected entries survive; table is re-read at each index and no retry occurs for already passed indices. Afterwards writes DWORD7B8E10=0,
// calls4BFCE0 noop, and resets DWORD662DC4 to0x7FFFFFFF. Does not clear initialization BYTE7B8E18, force-empty list sentinels, or discard protected table entries.
void rf_object_delete_unprotected_slots_and_reset_counter()
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 1024; ++i )
  {
    if ( unk_7B7E10[i] )
    {
      if ( (*(_DWORD *)(unk_7B7E10[i] + 124) & 0x800) == 0 )
        rf_object_delete_dispatch((_DWORD *)unk_7B7E10[i]);
    }
  }
  unk_7B8E10 = 0;
  rf_hook_4BFCE0_noop();
  dword_662DC4 = 0x7FFFFFFF;
}

