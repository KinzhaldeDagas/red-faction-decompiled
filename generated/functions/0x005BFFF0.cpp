// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BFFF0 rf_sound_group_gains_reset_unity
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly, x87 return flow and callers): Sets all four floats at 1DAE7B8 to 1.0. EAX is the completed loop count, not a status contract.
int rf_sound_group_gains_reset_unity()
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < 4; ++i )
  {
    unk_1DAE7B8[i] = 1.0;
    result = i + 1;
  }
  return result;
}

