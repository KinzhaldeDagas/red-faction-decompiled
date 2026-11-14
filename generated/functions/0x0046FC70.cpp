// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FC70 rf_ui_control_absolute_x
// UNREALRED VERIFIED [cutscene-ui-20261028]: Returns local signed integer x at this+12 plus recursively resolved parent x when parent pointer+4 is nonnull. Does not check cycles or overflow; null this is invalid.
int __thiscall rf_ui_control_absolute_x(_DWORD *this)
{
  if ( *(this + 1) )
    return *(this + 3) + rf_ui_control_absolute_x((_DWORD *)*(this + 1));
  else
    return *(this + 3);
}

