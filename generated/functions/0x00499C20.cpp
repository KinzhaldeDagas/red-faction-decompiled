// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499C20 rf_ctf_red_home_position_copy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Cdecl(destination vector pointer), returns the original destination pointer in EAX. Copies three floats from saved red home position77D714 when initialized byte77D6E2 is ANY
// nonzero value; otherwise copies shared fallback vector17F10B0. Does not return a borrowed reference to flag/current position and does not check mode, authority, destination or flag
// pointer. Fallback refers to shared runtime data, not an established immutable zero constant.
float *__cdecl rf_ctf_red_home_position_copy(float *a1)
{
  if ( byte_77D6E2 )
    rf_vector3_copy_return_destination(a1, unk_77D714);
  else
    rf_vector3_copy_return_destination(a1, flt_17F10B0);
  return a1;
}

