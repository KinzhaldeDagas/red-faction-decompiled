// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00475C60 rf_ambient_sound_find_by_uid
// UNREALRED VERIFIED [world-uid-ownership]: Scans the ambient-sound intrusive list and returns the first record whose UID at +0x08 matches the requested value.
// UNREALRED VERIFIED [ambient-audio]: Returns the first persistent ambient record whose UID at +8 matches the requested value.
int *__cdecl rf_ambient_sound_find_by_uid(int a1)
{
  _DWORD *i; // [esp+0h] [ebp-4h]

  for ( i = (_DWORD *)rf_ambient_sound_list_head; i != &rf_ambient_sound_list_head; i = (_DWORD *)*i )
  {
    if ( i[2] == a1 )
      return i;
  }
  return nullptr;
}

