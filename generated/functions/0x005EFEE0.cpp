// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005EFEE0 rf_ui_button_is_pressed_visual
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): True if state632==1;or state2/3 and owner hover target==this;or repeat flag2 set and state6/7. No visibility/disabled checks. State4drag alone returns false;button drawing separately treats global drag source as pressed.
bool __thiscall rf_ui_button_is_pressed_visual(_DWORD *this)
{
  return *(this + 158) == 1
      || (*(this + 158) == 2 || *(this + 158) == 3) && rf_ui_gadget_is_owner_hover_target(this)
      || (*(this + 157) & 2) != 0 && (*(this + 158) == 6 || *(this + 158) == 7);
}

