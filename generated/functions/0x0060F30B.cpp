// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F30B ?unexpected@@YAXXZ
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Get thread data, load raw callback at thread+124. NonNULL callback invoked with NO explicit args. Whether missing callback or callback returns,
// TAIL JMP terminate. No encode/decode of this thread callback, handler-result check, own return, reset or catch boundary. A throwing callback follows runtime unwind externally.
void __cdecl __noreturn unexpected()
{
  void (*v0)(void); // eax

  v0 = (void (*)(void))_getptd()[31];
  if ( v0 )
    v0();
  terminate();
}

