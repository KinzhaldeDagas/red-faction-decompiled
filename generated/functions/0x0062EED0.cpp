// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062EED0 sub_62EED0
// UNREALRED VERIFIED [combat-native-pickups-20261111]: Static item definitions are exactly96 records, stride0x50, base6F9130; destructor iterator passes those literal operands and49FAF0. This proves physical domain independently of the unchecked parser loop.
void sub_62EED0()
{
  `eh vector destructor iterator'(byte_6F9130, 0x50u, 96, (void (__thiscall *)(void *))rf_two_rfstring_prefix_destroy);
}

