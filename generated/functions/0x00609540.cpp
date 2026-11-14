// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00609540 __alloca_probe
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Special stack-growth helper, NOT an ordinary C
// allocation-return ABI. Entry ESP=S addresses returnPC; EAX is raw requested growth, ECX saved/restored. Compute target=S-EAX, saturating target0 on unsigned underflow. Starting
// floor((S-4)/4096)*4096, while unsigned target<page, subtract4096 then TEST DWORD[page] to touch/probe each page. Once reached target: EAX=target, restore ECX; XCHG EAX,ESP makes
// ESP=target and EAX=S; load old returnPC from[S], store it at[target], RET from relocated slot. Normal final ESP=target+4 (S-request+4 without underflow), EAX=old returnPC, not a
// destination pointer; EDX/other registers untouched, condition flags changed. No NULL/capacity/new-handler/heap interaction. Pseudocode drops TEST memory touches and hides stack
// relocation; native instructions are authoritative. Existing generic usercall type retained, but ECX is preserved scratch, not a semantic second argument.
void *__usercall _alloca_probe@<eax>(unsigned int a1@<eax>, int a2@<ecx>)
{
  unsigned int v2; // ecx
  unsigned int i; // eax
  int v5; // [esp-4h] [ebp-4h] BYREF
  _UNKNOWN *retaddr; // [esp+0h] [ebp+0h] BYREF

  v5 = a2;
  v2 = ~((unsigned int)((unsigned int)&retaddr - (unsigned __int64)a1) >> 32) & ((unsigned int)&retaddr - a1);
  for ( i = (unsigned int)&v5 & 0xFFFFF000; v2 < i; i -= 4096 )
    ;
  return retaddr;
}

