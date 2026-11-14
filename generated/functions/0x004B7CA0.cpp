// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B7CA0 rf_object_lists_and_free_slots_initialize_once
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, object lifetime/free-slot/attachment/render chains, original dispatch tables and field widths and native
// signed/x87/stack/callback ABI): No argument initialization guarded by BYTE7B8E18==EXACT1; every other byte value initializes. Sets common live-list sentinel7D0C80 next/previous
// at+16/+20 to itself, initializes free-list sentinel7B4DFC next/tail to itself, writes WORD7B4E08=1 (not a DWORD), and clears active-count DWORD7B4DF8. For signed i=0..1023
// initializes 12-byte free node7B4E10+12*i with DWORD index at+8 and appends it in ascending order using next+0/previous+4. Calls collision-pair pool initialization8192, then writes
// BYTE latch=1. Does not clear object table7B7E10 or protected-object state here. EAX is initial zero-extended latch on skipped path, otherwise incidental initializer result; no
// uniform success boolean.
int rf_object_lists_and_free_slots_initialize_once()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = unk_7B8E18;
  if ( unk_7B8E18 != 1 )
  {
    unk_7D0C90 = &unk_7D0C80;
    unk_7D0C94 = &unk_7D0C80;
    dword_7B4DFC = &dword_7B4DFC;
    unk_7B4E00 = &dword_7B4DFC;
    unk_7B4E08 = 1;
    unk_7B4DF8 = 0;
    for ( i = 0; i < 1024; ++i )
    {
      unk_7B4E18[3 * i] = i;
      unk_7B4E14[3 * i] = unk_7B4E00;
      unk_7B4E10[3 * i] = (int)&dword_7B4DFC;
      *unk_7B4E00 = &unk_7B4E10[3 * i];
      unk_7B4E00 = &unk_7B4E10[3 * i];
    }
    result = rf_collision_pair_pool_initialize8192();
    unk_7B8E18 = 1;
  }
  return result;
}

