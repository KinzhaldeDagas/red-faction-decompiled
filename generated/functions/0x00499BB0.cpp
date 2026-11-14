// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499BB0 rf_ctf_blue_carrier_get
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF carrier transforms, return/capture ordering, scoring and packet layouts): 
// No-argument raw getter of DWORD77D6DC, the blue flag carrier player pointer. No mode/authority check, validation or mutation; may return null.
int rf_ctf_blue_carrier_get()
{
  return unk_77D6DC;
}

