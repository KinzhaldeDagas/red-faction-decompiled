// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00619755 __NLG_Notify
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Internal EAX destination,EBP frame and ONE stack codeDWORD,calleeRET4. SaveEBX/ECX,loadglobal665EE0 andstackcode;store
// global+8=code,+4=destination,+12=frame. Extra PUSH/POP EBP/ECX/EAX preserve registers across notification site;restoreECX/EBX andRET4. No function callback/WinAPI/log output or
// data allocation; EAX destination retained, stackcode consumed.
int __userpurge _NLG_Notify@<eax>(int result@<eax>, int a2@<ebp>, int a3)
{
  unk_665EE8 = a3;
  unk_665EE4 = result;
  unk_665EEC = a2;
  return result;
}

