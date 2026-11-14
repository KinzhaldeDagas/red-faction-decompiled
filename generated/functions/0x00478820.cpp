// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00478820 rf_bolt_emitter_find_by_uid
// UNREALRED VERIFIED [world-uid-ownership]: Scans the section-0xE00 bolt-emitter pointer registry and returns the record whose UID at +0x00 matches the requested value.
int __cdecl rf_bolt_emitter_find_by_uid(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(rf_bolt_emitter_registry); ++i )
  {
    if ( **(_DWORD **)sub_552200(rf_bolt_emitter_registry, i) == a1 )
      return *(_DWORD *)sub_552200(rf_bolt_emitter_registry, i);
  }
  return 0;
}

