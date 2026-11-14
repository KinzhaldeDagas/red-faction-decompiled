// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059F400 rf_constant_one_59F400
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No consumed arguments, plainRET. Unconditionally assigns full EAX=1 then returns; no receiver/object/global read, data write, helper call, FPU operation or
// conditional branch. Result is constant signed32, not evidence of a particular entity/game/SDK predicate or index lookup. Incoming ECX/extra caller slots ignored; callee does not
// pop stack arguments. Existing library classification retained because generic constant-return native bytes do not prove RF ownership; caller usage alone is not treated as
// source-origin proof.
int rf_constant_one_59F400()
{
  return 1;
}

