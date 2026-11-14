// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005FF4E0 rf_jpeg_marker_emit_byte
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmarker.c:emit_byte matched): WriteslowBYTEvalue atdest24.next_output_byte0,postincrementsoutputpointer,decrementsunsignedfree_in_buffer4. Whenfreecountbecomes0,call dest.empty_output_buffer+12;FALSE triggersfatal24 CantSuspend. No check forinitialNULL/fullbuffer/freecount0 or0xFFstuffing;markergenerationmustnot suspend. APIvoid,return incidentalremainingcount/callbackresult.
int __cdecl rf_jpeg_marker_emit_byte(_DWORD *a1, char a2)
{
  int result; // eax
  int v3; // [esp+0h] [ebp-4h]

  v3 = a1[6];
  *(_BYTE *)(*(_DWORD *)v3)++ = a2;
  result = *(_DWORD *)(v3 + 4) - 1;
  *(_DWORD *)(v3 + 4) = result;
  if ( !*(_DWORD *)(v3 + 4) )
  {
    result = (*(int (__cdecl **)(_DWORD *))(v3 + 12))(a1);
    if ( !result )
    {
      *(_DWORD *)(*a1 + 20) = 24;
      return (*(int (__cdecl **)(_DWORD *))*a1)(a1);
    }
  }
  return result;
}

