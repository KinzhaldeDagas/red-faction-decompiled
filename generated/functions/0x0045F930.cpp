// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0045F930 rf_ui_control_clear_state_byte9
// UNREALRED VERIFIED [cutscene-ui-20261028]: Writes byte this+9=0 and returns this. No child propagation; exact product meaning of byte9 is not established by this body.
_BYTE *__thiscall rf_ui_control_clear_state_byte9(_BYTE *this)
{
  *(this + 9) = 0;
  return this;
}

