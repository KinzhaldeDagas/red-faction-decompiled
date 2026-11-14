// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0049FAF0 rf_two_rfstring_prefix_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, join/browser/roster payload codecs, native admission predicates, item bitmaps, logging clock ABI and peer update arithmetic): 
// Thiscall(record), no stack args. Destroys RFString at receiver+8 FIRST and receiver+0 SECOND. Does not free receiver storage, clear following scalars, know complete record stride,
// or dispose whole network/player object. Shared by36-byte join-request locals and weapon animation records whose two-string prefix is identical; existing constructor4270 is likewise
// shared. SEH cleanup thunks are part of function chunks; no semantic return value.
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, allocation/header ownership, exception and callback stack ABI, original rule tables and UI/flag apply
// ordering): Additional verified caller45DF80 passes this callback to EH vector destructor iterator withstride16 and count from allocation header. Prefix destructor itself remains
// generic:destroy RFString+8 then0 only,not whole-record deallocation or fixed28/36-byte stride. Vector/scalar delete flags and storage release belong to45DF80;array
// reallocator/clear/destructor useflags3. Existing weapon/networking callers and native thiscall/no-stack ABI unchanged.
void __thiscall rf_two_rfstring_prefix_destroy(char *this)
{
  rf_string_destroy_buffer(this + 8);
  rf_string_destroy_buffer(this);
}

