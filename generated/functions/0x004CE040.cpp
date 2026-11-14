// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004CE040 rf_particle_emitter_cached_room_visibility_byte
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, particle pool/list ownership, native damage admission, emitter initialization and cleanup): 
// Thiscall emitter, returns AL=0 when cached room DWORD +76 is null; otherwise returns raw room BYTE +352. No Boolean normalization: nonzero values other than 1 remain unchanged.
// Used by particle updates to gate owner-associated particles; does not resolve a new room or inspect emitter enabled +320.
char __thiscall rf_particle_emitter_cached_room_visibility_byte(_DWORD *this)
{
  if ( *(this + 19) )
    return *(_BYTE *)(*(this + 19) + 352);
  else
    return 0;
}

