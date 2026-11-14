// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F0160 rf_ui_button_get_press_relative_draw_origin
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): Writes absolute gadget X minus stored press X+900,and absolute Y minus stored press Y+904 to outputs;returns resulting Y. No state/drag check. Stored press coordinates are captured by input handler for mouse press.
int __thiscall rf_ui_button_get_press_relative_draw_origin(_DWORD *this, _DWORD *a2, int *a3)
{
  int result; // eax

  *a2 = rf_ui_gadget_absolute_x(this, 0) - *(this + 225);
  result = rf_ui_gadget_absolute_y(this, 0) - *(this + 226);
  *a3 = result;
  return result;
}

