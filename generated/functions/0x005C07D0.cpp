// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C07D0 rf_sound_backend_release_unreferenced
// UNREALRED VERIFIED [sound-backend]: Asks the active lower backend to release unreferenced sound resources, with the argument controlling the additional cleanup branch.
char *__cdecl rf_sound_backend_release_unreferenced(unsigned __int8 a1)
{
  char *result; // eax

  rf_sound_backend_stop_release_all_voices();
  result = (char *)a1;
  if ( !a1 )
    return rf_sound_resources_release_all_unpinned();
  return result;
}

