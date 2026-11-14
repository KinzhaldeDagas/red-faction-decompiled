// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00565EE0 rf_model_handle_get_character_instance_or_null
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, private material ownership/float-array copying, sparse geometry bounds, RGB packet bytes and cache retention/removal): Returns DWORD4 only if tag==2,otherwiseNULL. No instance validity, animation state or tag-independent pointer access.
int __cdecl rf_model_handle_get_character_instance_or_null(_DWORD *a1)
{
  if ( *a1 == 2 )
    return a1[1];
  else
    return 0;
}

