// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00499CA0 rf_ctf_blue_home_position_copy
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, CTF variable state serialization, client payload state/timer ordering, native function boundaries and reliable packet queue admission): 
// Cdecl(destination vector pointer), returns original destination in EAX. Copies3 floats from saved blue home position77D720 for any nonzero initialized77D6E2; otherwise copies
// shared fallback vector17F10B0. No mode/authority/destination/flag validation. Uses saved home rather than live common/current/predicted position; fallback vector contents are
// runtime data.
float *__cdecl rf_ctf_blue_home_position_copy(float *a1)
{
  if ( byte_77D6E2 )
    rf_vector3_copy_return_destination(a1, unk_77D720);
  else
    rf_vector3_copy_return_destination(a1, flt_17F10B0);
  return a1;
}

