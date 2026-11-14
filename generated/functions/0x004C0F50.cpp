// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C0F50 rf_bolt_emitter_reallocate_slot_geometry
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, four-slot emitter lifecycle, allocation and constructor layouts, native ordered lifetime gates, attachment transforms and paused rendering): 
// Recovered original33B code body4C0F50..4C0F71, thiscall receiver,signed requestedCount RET4. First releases ALL four slot resources via4C0760 (point objects, array backing and
// curve objects), then4C0630 allocates new four curve/point sets from requestedCount. Allocation helper resets life0 and replaces curve pointers; normal release clears array headers
// first. No attempt to preserve active bolts/control coordinates, rearm timestamp384, change flags/active byte, refresh cached room or validate requestedCount. No own rollback;
// allocation failure behavior inherited. No direct code xrefs currently present; recovery based on complete original PE prologue/body/RET and direct verified helper calls, not
// evidence this unused routine executes at runtime.
void __thiscall rf_bolt_emitter_reallocate_slot_geometry(void *this, int requestedCount)
{
  rf_bolt_emitter_release_slot_resources((void **)this);
  rf_bolt_emitter_allocate_four_slot_geometry((float *)this, requestedCount);
}

