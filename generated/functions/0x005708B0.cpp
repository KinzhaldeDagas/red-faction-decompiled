// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005708B0 rf_console_line261_construct_noop
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Thiscall receiver,no stack args. Calls verified no-op RGBA8 default constructor at receiver+257,then returns receiver;therefore initializes NO object bytes,including text and color. Global initializer62DD10 applies to500 records,stride105h=261,base180A5B0;62DD30 also constructs singleton180A4A0. Layout supports257-byte text area followed4 color bytes,but this function does not terminate/clear text or set RGBA.
int __thiscall rf_console_line261_construct_noop(int this)
{
  rf_rgba8_default_construct_noop((void *)(this + 257));
  return this;
}

