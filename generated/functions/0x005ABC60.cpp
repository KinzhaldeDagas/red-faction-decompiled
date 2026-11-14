// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ABC60 rf_ui_gadget_clear_two_key_slots
// UNREALRED VERIFIED [ui-properties-20261029]: Thiscall stores-1 in DWORDs+588 and+592,returns loop result2. Does not clear global key queue,callbacks,focus or other gadget fields.
int __thiscall rf_ui_gadget_clear_two_key_slots(_DWORD *this)
{
  int result; // eax
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < 2; ++i )
  {
    *(this + i + 147) = -1;
    result = i + 1;
  }
  return result;
}

