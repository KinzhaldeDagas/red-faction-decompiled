// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499DB0 rf_ctf_blue_capture_byte_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// No-argument raw getter. Loads blue capture BYTE77D6E1 into AL, leaving upper EAX bits incidental. No mode/authority/initialized guard or mutation; callers choose
// extension/signedness.
char rf_ctf_blue_capture_byte_get()
{
  return byte_77D6E1;
}

