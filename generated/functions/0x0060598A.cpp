// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060598A crt_noop_ret_0060598a
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Single native C3 RET. No argument consumption, receiver/global/local memory access, register/flag assignment, helper call, cleanup or semantic return value.
// EAX remains incoming residue; caller-supplied stack slots, if any, are not consumed. Existing classification preserved; absence of work does not prove an original RF class.
void crt_noop_ret_0060598a()
{
  ;
}

