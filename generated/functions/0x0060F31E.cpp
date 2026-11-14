// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F31E ?_inconsistency@@YAXXZ
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs inconsistency: decode global handler20213C0
// BEFORE try; nonNULL noargs callback is enclosed in catch-all EH4 scope65EC60, filter60F342 returns1, handler60F346 restores ESP. Normal/caught completion clears try level then
// terminate. NULL goes directly terminate. Pointer-decode exceptions occur outside protected call. No own arguments, lock, handler return interpretation or recovery return.
void __cdecl __noreturn _inconsistency()
{
  void (*v0)(void); // eax

  v0 = (void (*)(void))_decode_pointer(unk_20213C0);
  if ( v0 )
    v0();
  terminate();
}

