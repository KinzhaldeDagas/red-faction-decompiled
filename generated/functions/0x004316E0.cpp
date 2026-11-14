// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004316E0 sub_4316E0
// UNREALRED VERIFIED [entity-speech-lifecycle-20261027] Message entity identifier lookup scans the entity runtime list from pointer at 0x68211C, follows owner+0x28C until sentinel 0x681E90, and compares identifier against owner+0x20. Returns matching owner or 0. This path is not rf_entity_resolve_handle: do not reinterpret event+0x2D0 as a generation-tagged handle.
int __cdecl sub_4316E0(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = unk_68211C; (_UNKNOWN *)i != &unk_681E90; i = *(_DWORD *)(i + 652) )
  {
    if ( *(_DWORD *)(i + 32) == a1 )
      return i;
  }
  return 0;
}

