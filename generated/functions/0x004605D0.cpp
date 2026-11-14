// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004605D0 rf_multiplayer_profile_latch_name_edit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Set edit-latchBYTE6F4AD5=1 only. Does NOT set name-dirtyBYTE6F4AD6,change text,send or commit;keyboard editor result separately sets dirty. No
// runtime/state guard or meaningful EAX assignment.
void rf_multiplayer_profile_latch_name_edit()
{
  unk_6F4AD5 = 1;
}

