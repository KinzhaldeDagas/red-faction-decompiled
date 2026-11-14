// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499DA0 rf_ctf_red_capture_byte_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// No-argument raw getter. Loads red capture BYTE77D6E0 into AL with no mode, authority or initialized guard, no sign/zero extension into full EAX and no mutation. Consumers decide
// signedness/extension; the stored byte wraps naturally under capture increment helper.
char rf_ctf_red_capture_byte_get()
{
  return byte_77D6E0;
}

