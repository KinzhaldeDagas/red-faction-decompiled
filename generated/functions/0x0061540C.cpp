// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061540C __local_unwind4
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): EH4 local unwind with implicit parent EBP and three
// caller-popped stack DWORDs (cookie pointer, registration, unsigned target level). Return EAX is incidental, no semantic result. Install temporary FS:[0] guard at ESP after pushes:
// offsets 0 previous,4 handler 0x61549C,8 globalCookie XOR guardAddress,12 target,16 registration,20 callerCookiePointer,24 saved parent EBP. Decode scope table with
// *callerCookiePointer, distinct from global guard cookie. Stop at level -2, or target!=-2 and UNSIGNED level<=target. Publish entry.enclosing to registration+12 BEFORE callback.
// NonNULL filter is skipped; NULL filter executes finally: NLG_Notify(destination,EBP,0x101) consumes its code slot; ECX=1 then NLG_Call invokes EAX destination with no explicit
// stack arguments. Reload registration/table/level on loop. Restore FS:[0], discard guard, restore nonvolatiles, plain RET; no normal guard-cookie check. Secondary native entry
// 0x61549C (_unwind_handler4) belongs to this SAME function: flags&6 clear returns1; otherwise verify guard cookie (stored XOR guard address), load parent EBP from guard+24,
// recursively unwind with saved cookie pointer/frame/target, publish guard through fourth stack argument, return3. Secondary entry has four ordinary stack slots, not a separate
// function. No callback/table/NULL/range/cycle validation; -1 is not the -2 sentinel.
void __usercall _local_unwind4(void *a1@<ebp>, const unsigned int *a2, _DWORD *a3, unsigned int a4)
{
  unsigned int v4; // esi
  int v5; // esi
  unsigned int v6; // ebx
  _DWORD v7[10]; // [esp-8h] [ebp-28h] BYREF

  v7[5] = a2;
  v7[4] = a3;
  v7[3] = a4;
  v7[1] = &_unwind_handler4;
  v7[0] = NtCurrentTeb()->NtTib.ExceptionList;
  v7[2] = (unsigned int)v7 ^ dword_664BD8;
  while ( 1 )
  {
    v4 = a3[3];
    if ( v4 == -2 || a4 != -2 && v4 <= a4 )
      break;
    v5 = 3 * v4;
    v6 = (*a2 ^ a3[2]) + 4 * v5 + 16;
    a3[3] = *(_DWORD *)((*a2 ^ a3[2]) + 4 * v5 + 0x10);
    if ( !*(_DWORD *)(v6 + 4) )
    {
      _NLG_Notify(*(_DWORD *)(v6 + 8), (int)a1, 257);
      _NLG_Call(*(int (**)(void))(v6 + 8));
    }
  }
}

