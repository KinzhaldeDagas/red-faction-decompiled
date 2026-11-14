// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060A3D4 __amsg_exit
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(runtimeMessageID), callsFF_MSGBANNER
// thenNMSG_WRITE(ID). DecodeLIVE exit-handler pointer664D58; cdecl handler(255), thenreclaim allthree outstanding slots (message argument, decode argument, exit argument),return
// handlerEAX if it returns. No unconditional ExitProcess fallback in this body, handlerNULL check, own errno/invalid handler or guaranteed nonreturn. Encoded global controls
// fatal-exit policy.
int __cdecl _amsg_exit(int a1)
{
  int (__cdecl *v1)(int); // eax

  _FF_MSGBANNER();
  _NMSG_WRITE(a1);
  v1 = (int (__cdecl *)(int))_decode_pointer(off_664D58);
  return v1(255);
}

