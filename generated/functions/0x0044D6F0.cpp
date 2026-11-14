// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0044D6F0 rf_hud_persona_record_construct_members
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall required receiver, no stack args, plain RET; normal EAX explicitly returns original receiver. Constructs empty RFStrings at0,8,16 in order, then
// calls timestamp constructor at292, which writes exactly DWORD-1 without querying time. All other object fields, including the large24..291 span, remain unchanged; no whole-record
// zeroing, receiver allocation, resource loading, previous ownership cleanup or validation. Three-state PE unwind map65915C and second native chunk destroy completed strings16/8/0 in
// reverse order if a later construction step throws; timestamp has no mapped destructor. Normal success disables unwind actions. Fresh startup62A510 supplies this constructor plus
// HUD destructor44D770 for10 records of296-byte stride at6EF1A0; RF-specific member composition/caller initialization context disproves the inherited Concurrency/NUMA constructor
// label; no further gameplay struct or scalar meaning is inferred.
void *__thiscall rf_hud_persona_record_construct_members(void *self)
{
  rf_string_construct_empty(self);
  rf_string_construct_empty((_DWORD *)self + 2);
  rf_string_construct_empty((_DWORD *)self + 4);
  rf_timestamp4_construct_invalid((int *)self + 73);
  return self;
}

