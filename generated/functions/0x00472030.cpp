// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00472030 rf_ui_meta_control_set_flag9
// UNREALRED VERIFIED [cutscene-ui-20261028]: Calls 0x45F910 on group, then for each child pointer at group+40+4*i invokes child virtual byte offset12 with child in ECX, no explicit arguments. Count+168 reread per iteration. Propagates state through virtual calls; no null-child or count-bound guard. Return register is base pointer for empty group or loop index for nonempty group, not boolean status.
_BYTE *__thiscall rf_ui_meta_control_set_flag9(_DWORD *this)
{
  _BYTE *result; // eax
  int i; // [esp+4h] [ebp-4h]

  result = rf_ui_control_set_state_byte9(this);
  for ( i = 0; i < *(this + 42); ++i )
  {
    (*(void (__thiscall **)(_DWORD))(*(_DWORD *)*(this + i + 10) + 12))(*(this + i + 10));
    result = (_BYTE *)(i + 1);
  }
  return result;
}

