// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00478880 rf_push_region_find_by_uid
// UNREALRED VERIFIED [combat-push-region-state-20261104]: UID lookup iterates section-0x1100 push-region registry from index zero and returns immediately at first matching record +0x04. There is no UID-zero exclusion or uniqueness enforcement. Runtime state must retain ordered duplicate region records; a mission write changes only the first matching UID record.
int __cdecl rf_push_region_find_by_uid(int a1)
{
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(rf_push_region_registry); ++i )
  {
    if ( *(_DWORD *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 4) == a1 )
      return *(_DWORD *)sub_552200(rf_push_region_registry, i);
  }
  return 0;
}

