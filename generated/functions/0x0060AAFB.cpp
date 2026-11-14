// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060AAFB _fast_error_exit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Cdecl runtime message ID. Exactly global20213A8==1 calls FF_MSGBANNER first; other values skip. Push original messageID to NMSG_WRITE. Its4-byte argument
// remains when pushing literal255 for crtExitProcess; no cleanup needed on normal noreturn route. No ordinary return/handler loop/retry; final process termination code255 is
// independent of messageID.
void __cdecl __noreturn fast_error_exit(int a1)
{
  if ( unk_20213A8 == 1 )
    _FF_MSGBANNER();
  _NMSG_WRITE(a1);
  __crtExitProcess(0xFFu);
}

