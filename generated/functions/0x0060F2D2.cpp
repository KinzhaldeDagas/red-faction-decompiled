// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F2D2 ?terminate@@YAXXZ
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs terminate: getptd (may allocate/fatal), read
// RAW handler PTD+120, without pointer decoding. NonNULL handler called noargs inside EH4 scope65EC40; filter60F2F2 returns1 for any exception, handler60F2F6 restores ESP.
// Normal/caught completion clears try level then calls abort. NULL handler goes directly abort. PTD getter occurs before try; no own lock or handler return-value interpretation.
// Callback exceptions within scope are suppressed before abort.
void __cdecl __noreturn terminate()
{
  void (*v0)(void); // eax

  v0 = (void (*)(void))_getptd()[30];
  if ( v0 )
    v0();
  abort();
}

