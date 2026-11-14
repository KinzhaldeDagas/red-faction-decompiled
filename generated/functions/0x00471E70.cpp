// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471E70 rf_ui_choice_cycle_next
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): ECX choice control;EDX only scratch,not a second consumed argument. If countDWORD360==0,no write. ANY nonzero count
// ->increment indexDWORD364,if signed newIndex>=count store0. No positivity/current-index lower-bound validation,callback,sound,string copy or registry write. Native32-bit arithmetic
// can wrap;does not normalize corrupted negative index independently. EAX pointer/index residue,not uniform selected-index/status;existing one-ECX fastcall type retained.
int __fastcall rf_ui_choice_cycle_next(int a1)
{
  int result; // eax

  result = a1;
  if ( *(_DWORD *)(a1 + 360) )
  {
    result = ++*(_DWORD *)(a1 + 364);
    if ( result >= *(_DWORD *)(a1 + 360) )
      *(_DWORD *)(a1 + 364) = 0;
  }
  return result;
}

