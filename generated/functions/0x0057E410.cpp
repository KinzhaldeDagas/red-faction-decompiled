// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057E410 rf_bitset_destroy
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, bitset loops and ownership, polygon projection, byte arenas, argument widths and original PE bytes): Thiscall wrapper forwards receiver to conditional owned-buffer release57E620,returns its EAX receiver. Does not free borrowed backing,reset count/ownership or clear bit data.
int __thiscall rf_bitset_destroy(void *this)
{
  return rf_bitset_release_owned_buffer((int)this);
}

