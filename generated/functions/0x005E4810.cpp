// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E4810 rf_vani_player_clear_sequence_handle_no_release
// UNREALRED VERIFIED [texture-conversion-20261028]: Ifbasehandle+92!=-1,executesemptyloop0..framecount+84-1andsetsbasehandle-1. DoesNOTreleaseanyframebitmaporunbindtextures. Returnsloopcountor thispointerdependingpath. No metadata/time/flagreset.
_DWORD *__thiscall rf_vani_player_clear_sequence_handle_no_release(_DWORD *this)
{
  _DWORD *result; // eax
  _DWORD *i; // [esp+4h] [ebp-4h]

  result = this;
  if ( *(this + 23) != -1 )
  {
    for ( i = nullptr; ; i = (_DWORD *)((char *)i + 1) )
    {
      result = i;
      if ( (int)i >= *(this + 21) )
        break;
    }
    *(this + 23) = -1;
  }
  return result;
}

