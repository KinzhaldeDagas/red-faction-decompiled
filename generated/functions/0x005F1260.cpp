// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F1260 rf_ui_base_set_enabled
// UNREALRED VERIFIED [ui-properties-20261029]: Actual thiscall object,enabled BYTE (inferred fastcall exposes unused EDX). Stores disabled BYTE+28=(enabled==0),so any nonzero input enables. If currently focused and new disabled byte1,clears global focus and emits virtual+4(event4,-99999). No visibility flag mutation or child traversal. Return varies among normalized disabled0/1,object pointer and callback result;not reliable success boolean.
int __fastcall rf_ui_base_set_enabled(_BYTE *a1, int a2, char a3)
{
  int result; // eax

  result = a3 == 0;
  a1[28] = result;
  if ( dword_1CF75D8 == (_DWORD *)a1 )
  {
    result = (int)a1;
    if ( a1[28] == 1 )
    {
      dword_1CF75D8 = nullptr;
      return (*(int (__thiscall **)(_BYTE *, int, int))(*(_DWORD *)a1 + 4))(a1, 4, -99999);
    }
  }
  return result;
}

