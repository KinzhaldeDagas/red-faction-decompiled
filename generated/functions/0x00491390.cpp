// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491390 rf_lag_compensation_record424_destroy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, client timeout latch and registry admission, RFString-array ownership, native lag-compensation snapshot/restore asymmetry, geometry contact limits and respawn slots): 
// Thiscall record; delegates common_embedded_destroy_pointer_array(receiver56),which destroys backing atnested252=snapshot308. No receiver free,entity restore,handle invalidation or
// snapshot-count reset; does not zero array header. Static32-record EH cleanup callback registered by62C3C0.
void __thiscall rf_lag_compensation_record424_destroy(void **this)
{
  rf_common_embedded_destroy_pointer_array(this + 14);
}

