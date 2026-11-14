// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005F54C0 rf_ui_inputbox_set_text_if_within_configured_limit
// UNREALRED VERIFIED (2026-10-29; original PE bytes, fresh disassembly/decompilation and callers): NULL source clears text632 and returns1. Otherwise unsigned strlen(source)<=raw DWORD max1408 copies entire NUL-terminated source unbounded to632 and returns1;too long returns0 without change. No hard256-byte storage limit,allow/reject validation,width check,events or cursor reset. Negative configured max compares as huge unsigned and can permit overflow.
int __thiscall rf_ui_inputbox_set_text_if_within_configured_limit(int this, const char *a2)
{
  char v3; // dl
  _BYTE *v4; // [esp+8h] [ebp-1Ch]
  const char *v5; // [esp+Ch] [ebp-18h]

  if ( a2 )
  {
    if ( strlen(a2) <= *(_DWORD *)(this + 1408) )
    {
      v5 = a2;
      v4 = (_BYTE *)(this + 632);
      do
      {
        v3 = *v5;
        *v4++ = *v5++;
      }
      while ( v3 );
      return 1;
    }
    else
    {
      return 0;
    }
  }
  else
  {
    *(_BYTE *)(this + 632) = 0;
    return 1;
  }
}

