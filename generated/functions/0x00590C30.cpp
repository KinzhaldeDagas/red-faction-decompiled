// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590C30 rf_dsound_stop_release_by_play_handle
// UNREALRED VERIFIED [dsound-buffers-20261028]: Resolves play handle0x591310; failure returns-1,else delegates0x58F3E0. Fade flag8 can cause delegated stop to do nothing; this wrapper does not clear it or force release.
int *__cdecl rf_dsound_stop_release_by_play_handle(int a1)
{
  int *result; // eax

  result = (int *)rf_dsound_find_buffer_slot_by_play_handle(a1);
  if ( (int)result >= 0 )
    return rf_dsound_buffer_slot_stop_release_unless_fading((int)result);
  return result;
}

