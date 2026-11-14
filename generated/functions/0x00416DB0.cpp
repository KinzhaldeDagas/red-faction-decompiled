// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00416DB0 rf_clutter_skin108_destroy_strings
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Thiscall record,no stackargs. EH destructor iterator destroys ALL12 RFStrings at12+8*i,regardless count8,then destroys name RFString0. Does NOT free containing108-byte record,look at active count,clear count or release any external glare-array entries. No pointer/count validity guard;used for temporaries and constructed array capacity slots.
void __thiscall rf_clutter_skin108_destroy_strings(char *this)
{
  `eh vector destructor iterator'(this + 12, 8u, 12, rf_string_destroy_buffer);
  rf_string_destroy_buffer(this);
}

