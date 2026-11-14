// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499BC0 rf_ctf_red_flag_home_or_uninitialized
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// No-argument canonical0/1 result in EAX. Returns true if initialized byte77D6E2 is zero; otherwise returns whether red flag77D6E4 instance DWORD+700 bit200 is set. No mode/authority
// guard, carrier-pointer check or mutation. When initialized is nonzero it dereferences red flag without null validation, including partially registered state. The initial MOVZX of
// initialized byte clears upper EAX, so later AL0/1 writes produce canonical full-EAX0/1.
bool rf_ctf_red_flag_home_or_uninitialized()
{
  return !byte_77D6E2 || (*(_DWORD *)(dword_77D6E4 + 700) & 0x200) != 0;
}

