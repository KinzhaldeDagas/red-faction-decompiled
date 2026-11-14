// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00483D30 rf_cutscene_segment32_construct_string
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, RFL region-version layouts, cutscene stream ABI and count bounds, constructor/destructor ownership and debris descriptor bits): 
// Thiscall32-byte segment constructor callback. Constructs only empty8-byte RFString at+24; leaves first24 scalar/id bytes untouched. Native EAX is receiver, ignored by EH iterator's
// void callback contract. No duration defaults, target resolution or pose construction. Containing sequence constructs64 slots of this stride; record loader fills numeric fields
// separately.
void __thiscall rf_cutscene_segment32_construct_string(_DWORD *this)
{
  rf_string_construct_empty(this + 6);
}

