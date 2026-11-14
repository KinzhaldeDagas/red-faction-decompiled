// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0046FCA0 rf_ui_control_absolute_y
// UNREALRED VERIFIED [cutscene-ui-20261028]: Returns local signed integer y at this+16 plus recursively resolved parent y when parent pointer+4 is nonnull. Does not check cycles or overflow; null this is invalid.
int __thiscall rf_ui_control_absolute_y(_DWORD *this)
{
  if ( *(this + 1) )
    return *(this + 4) + rf_ui_control_absolute_y((_DWORD *)*(this + 1));
  else
    return *(this + 4);
}

