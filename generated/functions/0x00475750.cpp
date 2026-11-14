// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475750 rf_ambient_sound_destroy
// UNREALRED VERIFIED [ambient-audio]: Unlinks one persistent ambient record. If it owns a frontend slot, source gain is cleared before record destruction; the slot itself remains frontend-owned until level reset.
void *__cdecl rf_ambient_sound_destroy(void *a1)
{
  void *result; // eax

  **((_DWORD **)a1 + 1) = *(_DWORD *)a1;
  *(_DWORD *)(*(_DWORD *)a1 + 4) = *((_DWORD *)a1 + 1);
  *(_DWORD *)a1 = 0;
  *((_DWORD *)a1 + 1) = 0;
  if ( *((int *)a1 + 4) > -1 )
    rf_ambient_voice_set_source_gain(*((_DWORD *)a1 + 4), 0.0);
  result = a1;
  if ( a1 )
    result = rf_ambient_sound_scalar_delete(a1, 1);
  --rf_ambient_sound_record_count;
  return result;
}

