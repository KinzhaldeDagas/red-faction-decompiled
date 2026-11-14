// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060CCF2 __purecall
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs, noreturn after normal callback completion
// (prototype supplied; existing noreturn flag retained). Decode purecall-handler slot2021C9C; if nonNULL invoke raw noargs callback without catch. If it returns, NMSG_WRITE25,
// set_abort_behavior(0,1) clears only message bit, tailjump abort. Callback may throw out; no own handler-argument reads, lock or error return.
void __cdecl __noreturn _purecall()
{
  void (*v0)(void); // eax

  v0 = (void (*)(void))_decode_pointer(unk_2021C9C);
  if ( v0 )
    v0();
  _NMSG_WRITE(25);
  _set_abort_behavior(0, 1u);
  abort();
}

