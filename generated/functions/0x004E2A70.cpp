// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2A70 rf_player_aux4608_record_construct
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Thiscall constructor, no stack arguments, return receiver. Calls4A6790(receiver+28), then timestamp4 invalid constructor(receiver+2500). Parent player-create allocates2504 bytes, stores pointer in player+4608, then independently initializes fields+16/+2488; these parent writes are not part of this constructor. No full-record zeroing. Embedded4A6790 performs its own deadline/array initialization; not a no-op and not evidence all2504 bytes are initialized.
int *__thiscall rf_player_aux4608_record_construct(int *this)
{
  rf_net_statistics_construct(this + 7);
  rf_timestamp4_construct_invalid(this + 625);
  return this;
}

