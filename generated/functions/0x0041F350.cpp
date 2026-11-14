// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041F350 rf_common_derived_destroy_string676_and_base
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): Void thiscall ECX common-derived record, no stack args/plainRET. First destroys RFString buffer at record+676 through55F6D0, then COMMON
// embedded members412580(record). No own NULL test, scalar operator delete, pool unlink or game-death behavior. This layout is not ordinary ENTITY selected-weapon DWORD+676. MSVC SEH
// state0->-1, unwind map658240 and attached622730 tail ensure COMMON cleanup if string destruction unwinds;622738 handler is misnamed CRT context, not evidence of concurrency
// semantics. Caller owns allocation lifetime.
void __thiscall rf_common_derived_destroy_string676_and_base(int this)
{
  rf_string_destroy_buffer((void *)(this + 676));
  rf_common_object_destroy_embedded_members(this);
}

