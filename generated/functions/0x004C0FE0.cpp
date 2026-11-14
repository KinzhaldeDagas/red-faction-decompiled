// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0FE0 rf_bolt_emitter_get_room_byte352
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Thiscall emitter. If cached room pointer108 NULL returns AL0; otherwise returns RAW BYTE room+352 unchanged, not normalized boolean. No pointer refresh, object/slot/active/lifetime
// check or mutation. Does not interpret other room fields.
char __thiscall rf_bolt_emitter_get_room_byte352(_DWORD *this)
{
  if ( *(this + 27) )
    return *(_BYTE *)(*(this + 27) + 352);
  else
    return 0;
}

