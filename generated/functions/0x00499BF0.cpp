// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499BF0 rf_ctf_blue_flag_home_or_uninitialized
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// No-argument canonical0/1 result in EAX. Returns true if initialized byte77D6E2 is zero; otherwise tests blue flag77D6E8 instance DWORD+700 home bit200. No
// game-mode/authority/carrier guard or mutation. Once initialized is nonzero blue pointer is unconditionally dereferenced; registration of red alone does not guarantee it. Initial
// MOVZX of initialized byte clears upper EAX, so AL0/1 writes yield full-EAX0/1.
bool rf_ctf_blue_flag_home_or_uninitialized()
{
  return !byte_77D6E2 || (*(_DWORD *)(dword_77D6E8 + 700) & 0x200) != 0;
}

