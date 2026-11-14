// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048A530 rf_object_move_dispatch_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, mover UID and handle queries, detachment and member ownership, original console packet serialization, native team-byte sentinel and authority comparisons): 
// Native five-byte no-op: push ebp,mov ebp/esp,pop ebp,ret. No body loads/stores, helper calls or stable return value; no callee argument pop. Referenced by
// object_move_one_type_dispatch at4B9510. Does not move or delete an object.
void rf_object_move_dispatch_noop()
{
  ;
}

