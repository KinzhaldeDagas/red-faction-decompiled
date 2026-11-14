// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477BD0 rf_level_state_bit0_is_set
// UNREALRED VERIFIED [save-validation-20261028]: Returns boolean(global0x6FC424 & 1). Called by quicksave eligibility; full semantic meaning of this global bit is not established here.
bool rf_level_state_bit0_is_set()
{
  return (unk_6FC424 & 1) != 0;
}

