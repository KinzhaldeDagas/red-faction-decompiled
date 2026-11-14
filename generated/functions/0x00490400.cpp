// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490400 rf_string_array8_construct_capacity
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Thiscall array receiver,capacity stack argument,RET4. Calls490420 initializer with capacity,then returns receiver regardless delegate EAX. No independent allocation guard or
// live-storage cleanup.
_DWORD *__thiscall rf_string_array8_construct_capacity(_DWORD *this, int a2)
{
  rf_string_array8_initialize_capacity(this, a2);
  return this;
}

