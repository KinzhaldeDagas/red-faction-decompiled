// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004B4160 rf_motion_sample_buffers_clear_registered_snap_flags
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, native buffered-motion insertion/sampling, asymmetric WORD time differences, temporary physics snapshot/restore and native list guards): Noargs. Traverses rings68211C/681E90 and70489C/704610 via object652. For each physics424 bit0x8000 AND nonNULL buffer632,calls3510 toclear ONLY buffer1320 bit2. Does not clear pendingbit1,advance cursor,reset samples or apply pose;no local-player exception/list validation. IncidentalEAX at exit,not changed-object count.
_DWORD *rf_motion_sample_buffers_clear_registered_snap_flags()
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
        result = rf_motion_sample_buffer_clear_snap_flag(*(_DWORD **)(i + 632));
    }
  }
  for ( j = unk_70489C; (_UNKNOWN *)j != &unk_704610; j = (int)result )
  {
    if ( (*(_DWORD *)(j + 424) & 0x8000) != 0 && *(_DWORD *)(j + 632) )
      rf_motion_sample_buffer_clear_snap_flag(*(_DWORD **)(j + 632));
    result = *(_DWORD **)(j + 652);
  }
  return result;
}

