// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499CE0 rf_ctf_blue_home_matrix_copy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Cdecl(destination matrix pointer), returns original destination in EAX. Copies9 floats from saved blue home matrix77D738 if initialized77D6E2 is any nonzero value; otherwise shared
// fallback matrix17F10EC. No mode/authority/destination/flag guard, and no borrowed-global return. Saved home matrix is independent of current common/physical orientation; shared
// fallback is not proven constant identity.
int __cdecl rf_ctf_blue_home_matrix_copy(int a1)
{
  if ( byte_77D6E2 )
    rf_matrix3_copy_construct(a1, &flt_77D738);
  else
    rf_matrix3_copy_construct(a1, flt_17F10EC);
  return a1;
}

