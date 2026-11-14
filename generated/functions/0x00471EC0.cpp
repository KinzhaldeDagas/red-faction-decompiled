// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00471EC0 rf_ui_choice_cycle_previous
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, multiplayer level catalog/control call chains, native header/string ABI, original setup tables, slider
// arithmetic, callback stack reuse and RFString array ownership): ECX choice control. countDWORD360==0 ->no write. Any nonzero count ->decrement indexDWORD364;only signed result<0
// stores count-1. No positive-count/index-upper-bound guard,callback,sound or registry write. Corrupted index>=count can remain above bound after decrement;negative count is not
// rejected separately. ReturnEAX incidental control/count residue,not uniform bool/index;prototype unchanged.
_DWORD *__thiscall rf_ui_choice_cycle_previous(_DWORD *this)
{
  _DWORD *result; // eax

  result = this;
  if ( *(this + 90) )
  {
    result = this;
    if ( (int)--*(this + 91) < 0 )
    {
      result = (_DWORD *)(*(this + 90) - 1);
      *(this + 91) = result;
    }
  }
  return result;
}

