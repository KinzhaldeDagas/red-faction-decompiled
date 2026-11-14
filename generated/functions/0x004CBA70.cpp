// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CBA70 rf_particle_decode_damage_nibble_half
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Cdecl particle120 pointer; returns the binary32-rounded value in x87 ST0: F32(((WORD[particle+78] & 0xF000) >> 12) * double 0.5). Mask removes sign extension before logical shift,
// yielding 0..7.5 in steps of 0.5. No mutation. Caller rf_particle_pool_update uses this as the base damage amount before its age-dependent scaling; this helper performs no lifetime
// or damage admission checks.
double __cdecl rf_particle_decode_damage_nibble_half(int a1)
{
  return (float)((double)((unsigned __int16)(*(_WORD *)(a1 + 78) & 0xF000) >> 12) * 0.5);
}

