// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004EF150 rf_undercover_initialize_runtime_state
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, thermal renderer x87 branches, native stack aliases, localization pool writes and skin-profile selection): No arguments. Clears bytes87FC01 and87FC00, performs literal case-insensitive registry lookup for Undercover 12mm handgun, stores result (including-1) at87FC1C, sets87FC08=-1 and returns lookup result. No model/texture loading or inventory changes.
int rf_undercover_initialize_runtime_state()
{
  int result; // eax

  unk_87FC01 = 0;
  unk_87FC00 = 0;
  result = sub_50FB80("Undercover 12mm handgun");
  dword_87FC1C = result;
  unk_87FC08 = -1;
  return result;
}

