// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B40B0 rf_motion_sample_buffers_advance_registered_objects
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): Noargs. Traverses ring head68211C until sentinel681E90,then head70489C until sentinel704610;next link object652. For each object physics424 bit0x8000 set AND buffer632nonNULL,calls3220(ECXbuffer,object). No entity identity exception (unlike motion dispatcher),NULL/list-corruption guard,snapshot list or global count. ReturnedEAX is incidental iteration/delegate state,not number updated;no direct pose interpolation.
_DWORD *rf_motion_sample_buffers_advance_registered_objects()
{
  _DWORD *result; // eax
  int i; // [esp+0h] [ebp-8h]
  int j; // [esp+4h] [ebp-4h]

  result = (_DWORD *)unk_68211C;
  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    result = (_DWORD *)i;
    if ( (*(_DWORD *)(i + 424) & 0x8000) != 0 )
    {
      if ( *(_DWORD *)(i + 632) )
        result = rf_motion_sample_buffer_advance_playback_cursor(*(_DWORD *)(i + 632), i);
    }
  }
  for ( j = unk_70489C; (_UNKNOWN *)j != &unk_704610; j = *(_DWORD *)(j + 652) )
  {
    if ( (*(_DWORD *)(j + 424) & 0x8000) != 0 && *(_DWORD *)(j + 632) )
      rf_motion_sample_buffer_advance_playback_cursor(*(_DWORD *)(j + 632), j);
    result = (_DWORD *)j;
  }
  return result;
}

