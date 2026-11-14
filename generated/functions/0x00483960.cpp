// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483960 rf_room_mp_tracking_eligible
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Thiscall room record; returns normalized AL Boolean: BYTE[room+0] must equal EXACT1 and BYTE[room+152] must equal0. No NULL guard or room mutation. Sole caller47E2B0 after geometry
// deserialization scans world room pointer array+144 in multiplayer mode1 and retains up to128 rooms satisfying this predicate. Does not resolve position, test liquid height,
// visibility byte352, or assign unproven meanings to these two raw flag bytes.
bool __thiscall rf_room_mp_tracking_eligible(_BYTE *this)
{
  return *this == 1 && !*(this + 152);
}

