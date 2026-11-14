// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1B00 rf_ui_state_image_attach_animation
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): If mode1,stores borrowed player pointer+8 and changes to3 preserving bitmap. Otherwise reset then store pointer+8 and mode2. Does not set ownership BYTE+28,configure player,validate pointer or load filename. Reset preserves stale fields in some cases;ownership semantics depend on existing record as documented at0x5F1950. Returns this.
_DWORD *__thiscall rf_ui_state_image_attach_animation(_DWORD *this, int a2)
{
  if ( *this == 1 )
  {
    *(this + 2) = a2;
    *this = 3;
    return this;
  }
  else
  {
    rf_ui_state_image_reset(this);
    *(this + 2) = a2;
    *this = 2;
    return this;
  }
}

