// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004788E0 rf_push_region_snapshot_collect
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Collect8-byte PUSH REGION records from rf_push_region_registry: key dword region+4 at entry+0, raw state byte region+0x68 at entry+4. BYTE count. No renderer light handle, geometry transform, full padding initialization or dynamic-region creation; this is not the light snapshot family.
int __cdecl rf_push_region_snapshot_collect(int a1, _BYTE *a2)
{
  int result; // eax
  int i; // [esp+0h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(rf_push_region_registry); ++i )
  {
    *(_DWORD *)(a1 + 8 * i) = *(_DWORD *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 4);
    *(_BYTE *)(a1 + 8 * i + 4) = *(_BYTE *)(*(_DWORD *)sub_552200(rf_push_region_registry, i) + 104);
  }
  result = rf_receiver_get_first_dword(rf_push_region_registry);
  *a2 = result;
  return result;
}

