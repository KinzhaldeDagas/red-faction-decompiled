// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0056D640 rf_console_command_record_register_sorted
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, console dispatch/lexing, history/ring layout, input/render paths, context-save calling convention and stream receivers): ECX12byte record plus(namePointer,helpPointer,callback),RET12,returns receiver. Global pointer table180A408 has capacity30,count180A480. If count>=30 returns WITHOUT initializing record. Otherwise case-insensitive sorted search: duplicate name returns without insertion or record initialization;greater name establishes insertion point,shifts prior pointers right,then increments count. Only successful registration writes receiver0=name,4=help,8=callback. Stores borrowed pointers,not copies; no NULL name/existing-entry validation or ownership transfer. Callback invoked later as cdecl noargs and return ignored.
_DWORD *__thiscall rf_console_command_record_register_sorted(_DWORD *this, char *String2, int a3, int a4)
{
  int j; // [esp+4h] [ebp-Ch]
  int v7; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  if ( dword_180A480 < 30 )
  {
    for ( i = 0; i < dword_180A480; ++i )
    {
      v7 = _stricmp(*(const char **)dword_180A408[i], String2);
      if ( !v7 )
        return this;
      if ( v7 > 0 )
        break;
    }
    if ( i >= dword_180A480 )
    {
      dword_180A408[dword_180A480++] = (int)this;
    }
    else
    {
      for ( j = dword_180A480; j > i; --j )
        dword_180A408[j] = dword_180A404[j];
      dword_180A408[i] = (int)this;
      ++dword_180A480;
    }
    *this = String2;
    *(this + 1) = a3;
    *(this + 2) = a4;
  }
  return this;
}

