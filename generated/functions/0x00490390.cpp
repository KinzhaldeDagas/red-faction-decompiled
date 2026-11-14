// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00490390 rf_multiplayer_session_record_construct_members
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Thiscall required receiver, no stack arguments, plain RET; normal EAX explicitly returns original receiver. Constructs empty RFStrings0 and8, then
// initializes RFString-array8 header at64 with capacity0 through490400 (empty count/capacity/backing header, no elements allocated or constructed). Does not clear scalar/padding
// bytes16..63 or any other object payload, allocate receiver, free previous string/array storage, validate pointers or check delegate result. Own shared2-state unwind map658928
// destroys completed string8 then0 if a later construction step throws; array64 is final and its own initializer owns any internal failure cleanup. Success disables unwind actions.
// Fresh startup62C290 invokes this receiver constructor on global704EC0 and registers62F0C0 cleanup; previously verified490460 destroys its two strings and rotation
// array64(global704F00). The fixed RFString/member-array composition and native startup owner establish an RF record constructor rather than inherited Concurrency/NUMA identity; no
// semantic role for untouched fields is invented.
void *__thiscall rf_multiplayer_session_record_construct_members(void *self)
{
  rf_string_construct_empty(self);
  rf_string_construct_empty((_DWORD *)self + 2);
  rf_string_array8_construct_capacity((char *)self + 64, 0);
  return self;
}

