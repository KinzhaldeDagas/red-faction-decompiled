// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004147A0 rf_clutter_reset_counter_and_allocated_bitset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter runtime teardown/render admission, DWORD-category glass callback, cached model binding and signed-counter clock-hand geometry): Noargs. Writes globalDWORD666B74=0;passes receiverHEADER address666FF0 and value0 to bitset fill helper,which memsets stored backing pointer for storedBYTE count,including paddingbits. Does not allocate,change stored byte count,clear sound throttle666B7C,clear clock registry666B78 or walk clutter list. Returns backing pointer/memset resultEAX,not bit count or success. No own header/backing validation.
void *rf_clutter_reset_counter_and_allocated_bitset()
{
  unk_666B74 = 0;
  return rf_bitset_fill_all_storage_bytes((int)&unk_666FF0, 0);
}

