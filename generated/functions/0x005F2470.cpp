// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F2470 rf_ui_checkbox_toggle_checked
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Logical NOT of raw BYTE+628:nonzero becomes0,zero becomes1. Returns this;no input/disabled checks,event19 emission or visual-state update.
_BYTE *__thiscall rf_ui_checkbox_toggle_checked(_BYTE *this)
{
  _BYTE *result; // eax

  result = this;
  if ( *(this + 628) )
  {
    *(this + 628) = 0;
  }
  else
  {
    *(this + 628) = 1;
    return this;
  }
  return result;
}

