// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C1610 rf_managed_particle_effect_get_room_byte352
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, managed emitter and voice ownership, original table parser, circular graph lifecycle, native unordered time gates and direct particle descriptor consumer): 
// Thiscall node. cachedRoom28 NULL ->AL0; otherwise returns raw BYTE room+352 without canonicalizing bool. No room refresh, position query, emitter validity, visibility calculation
// or mutation.
char __thiscall rf_managed_particle_effect_get_room_byte352(_DWORD *this)
{
  if ( *(this + 7) )
    return *(_BYTE *)(*(this + 7) + 352);
  else
    return 0;
}

