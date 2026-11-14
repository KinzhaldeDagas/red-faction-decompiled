// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00535A60 rf_face_unlink_decal_polygon_link
// UNREALRED VERIFIED [decal-face-links-20261028]: If face head+76 equals target, replaces head with target+1328, clears face flags+40 mask0x200000 ONLY when new headnull, clears target next. Else scans singly-linked+1328 and bypasses first matching target, clears target next. Absent target unchanged. Never clears face flag0x100000 or polygon face-owner+1312; no record free. Return value differs among branches, not a reliable success result.
_DWORD *__thiscall rf_face_unlink_decal_polygon_link(_DWORD *this, int a2)
{
  _DWORD *result; // eax
  _DWORD *i; // [esp+4h] [ebp-4h]

  result = this;
  if ( *(this + 19) )
  {
    if ( *(this + 19) == a2 )
    {
      *(this + 19) = *(_DWORD *)(a2 + 1328);
      result = this;
      if ( !*(this + 19) )
      {
        result = this;
        *(this + 10) &= ~0x200000u;
      }
      *(_DWORD *)(a2 + 1328) = 0;
    }
    else
    {
      result = (_DWORD *)*(this + 19);
      for ( i = result; i; i = (_DWORD *)i[332] )
      {
        if ( i[332] == a2 )
        {
          i[332] = *(_DWORD *)(a2 + 1328);
          *(_DWORD *)(a2 + 1328) = 0;
          return (_DWORD *)a2;
        }
      }
    }
  }
  return result;
}

