// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417550 rf_clutter_skin_array_destroy_members
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): For a nonnull base at header+8, calls skin vector-deleting destructor 0x4170D0 with flags 3. It destroys every cookie-capacity record, including spare records, and frees the allocation starting four bytes before base. Leaves header count/capacity/base unchanged and never frees the outer header. Null base returns receiver bits; populated path propagates incidental freed allocation bits, not a success code. Distinct from reusable header-clearing release 0x417050.
char *__thiscall rf_clutter_skin_array_destroy_members(char **this)
{
  char *result; // eax

  result = (char *)this;
  if ( *(this + 2) )
  {
    result = *(this + 2);
    if ( result )
      return rf_clutter_skin108_deleting_destructor(*(this + 2), 3);
  }
  return result;
}

