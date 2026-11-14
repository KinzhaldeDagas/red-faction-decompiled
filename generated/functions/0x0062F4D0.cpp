// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0062F4D0 sub_62F4D0
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Actual static cleanup uses EH vector destructor base911488,stride20,count32,callback49FAF0 (two RFStrings). Confirms physical32 ammo records independently of parsed count and independently of inventory reserve32. Parser unchecked overflow must not be described as native clamp/check.
void sub_62F4D0()
{
  `eh vector destructor iterator'(byte_911488, 0x14u, 32, (void (__thiscall *)(void *))rf_two_rfstring_prefix_destroy);
}

