// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F56A0 rf_ui_inputbox_release_cursor_animation
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): If cursor animation1440 nonNULL,calls VANI deleting destructor(flag1),then zeroes1440. Leaves cursor bitmap/dimensions and other fields unchanged. Return incidental this when absent or deleted pointer when present;not a success flag.
int *__thiscall rf_ui_inputbox_release_cursor_animation(int **this)
{
  int *result; // eax

  result = (int *)this;
  if ( *(this + 360) )
  {
    result = *(this + 360);
    if ( result )
      result = rf_vani_player_scalar_deleting_destructor(*(this + 360), 1);
    *(this + 360) = nullptr;
  }
  return result;
}

