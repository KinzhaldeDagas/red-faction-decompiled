// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006196A5 __local_unwind2
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Mixed ABI incoming EBP=parent funclet frame plus two
// caller-popped stack slots {legacyFrameRecord*,unsigned targetLevel},void (old incidental EAX frame-pointer result). Save EBX/ESI/EDI,build hand SEH guard:
// previousFS,unwind_handler619660,state-2,copy of input record,saved incomingEBP; prepend cookie at guard-4 =globalCookie XOR guardAddress,install FS:0=guard. Guard+24h/+28h point
// into original caller frame/target argument slots; +10h holds parentEBP. Own body never establishes a new EBP frame. Each loop reload input frame,scope tableDWORD frame+8,current
// levelDWORD+12. levelFFFFFFFF ->done. target!=FFFFFFFF AND UNSIGNED level<=target ->done; otherwise compute table+12*level modulo32. Load enclosing next level,store it into BOTH
// guard state+8 and frame.level+12 BEFORE any cleanup call. Nonzero entry.filter+4 skips callback,continues traversal; zero filter means finally,load entry.handler+8
// intoEAX,push101h,call verified NLG_Notify(EAX destination,live EBP,one RET4 compatibility code),reload handler EAX,call NLG_Call (CALL EAX thenRET,no explicit handler args). No
// NULL handler test. Reload loop; no signed-level validation,entry count,bounds,progress/cycle/overflow guard or status check. Normal done restores FS:0 from guard.previous,ADD ESP24
// discards cookie/guard,POP EDI/ESI/EBX,plainRET with incomingEBP still live under funclet convention. No normal cookie check (unwind_handler checks on unwind flag path),no own
// allocation/global log beyond NLG delegate. Guard participates in collided unwind; ordinary cleanup exceptions are not locally swallowed. Corrected prototype exposes EBP register
// input and removes misleading status result. Pseudocode does not represent full guard/stack restoration.
void __usercall _local_unwind2(void *a1@<ebp>, _DWORD *a2, unsigned int a3)
{
  int v3; // ebx
  unsigned int v4; // esi
  int v5; // esi

  while ( 1 )
  {
    v3 = a2[2];
    v4 = a2[3];
    if ( v4 == -1 || a3 != -1 && v4 <= a3 )
      break;
    v5 = 3 * v4;
    a2[3] = *(_DWORD *)(v3 + 4 * v5);
    if ( !*(_DWORD *)(v3 + 4 * v5 + 4) )
    {
      _NLG_Notify(*(_DWORD *)(v3 + 4 * v5 + 8), (int)a1, 257);
      _NLG_Call(*(int (**)(void))(v3 + 4 * v5 + 8));
    }
  }
}

