// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499C60 rf_ctf_red_home_matrix_copy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Cdecl(destination matrix pointer), returns original destination pointer in EAX. Copies nine floats from saved red home matrix77D6EC if initialized77D6E2 is nonzero; otherwise
// copies shared fallback matrix17F10EC. No mode, authority, destination or flag-pointer guard. Does not return the live flag common/physical matrix or a borrowed global reference;
// fallback is runtime shared data, not a proven constant identity matrix.
int __cdecl rf_ctf_red_home_matrix_copy(int a1)
{
  if ( byte_77D6E2 )
    rf_matrix3_copy_construct(a1, &flt_77D6EC);
  else
    rf_matrix3_copy_construct(a1, flt_17F10EC);
  return a1;
}

