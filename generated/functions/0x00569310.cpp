// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00569310 rf_music_owned_get_resource_record
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, sound wrapper ABI, triangle/plane interval tests, strict sphere overlap and retail SAT coefficients): cdecl NO arguments: entry PUSH ECX reserves local output slot,not an object receiver. If either owned backend voice1808954 or owned resource handle1808958 equals-1 returnsNULL. Otherwise passes resource handle and local output pointer to5C17D0 and returns resulting slot,ignoring helper status. Helper writes registry+64*unsignedIndex for index<2600 regardless readiness/population; other indices leave local slot unchanged,so invalid non--1 handle returns the incoming ECX bits saved by PUSH,not guaranteedNULL. No ownership/reference increment.
void *__cdecl rf_music_owned_get_resource_record()
{
  void *v0; // ecx
  void *v2; // [esp+0h] [ebp-4h] BYREF

  v2 = v0;
  if ( rf_music_owned_backend_voice == -1 || rf_music_owned_sound_handle == -1 )
    return nullptr;
  rf_sound_resource_get_record_out(rf_music_owned_sound_handle, &v2);
  return v2;
}

