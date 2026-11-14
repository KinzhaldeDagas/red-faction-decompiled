// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061974C __NLG_Notify1
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Alternate NLG entry. PUSH EBX/ECX,setEBX=global665EE0,JMP shared619760. Unlike619755 it does NOT load ECX from stack: uses incomingECX as notification code,
// EAX destination,EBP frame. Shared writes fields+8/+4/+12,preservesregisters andRET4 still discards one compatibility stack slot. Existing one-stack prototype does not express extra
// live-register inputs; native contract recorded explicitly.
void __stdcall _NLG_Notify1(int a1)
{
  JUMPOUT(0x619760);
}

