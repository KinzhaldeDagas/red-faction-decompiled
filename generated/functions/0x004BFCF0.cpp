// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BFCF0 rf_collision_register_object_against_active_list
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, fixed object-pool ownership and signed drain arithmetic, intrusive pair lists, allocation dispatch and native x87/register ABI): Cdecl object pointer. Type2 plus class616 mask0x20 first rebuilds four global projectile planes via4BE990. Then walks global COMMON active list head7D0C90/sentinel7D0C80,next16, calling4BEB80(input,each) for every entry INCLUDING input itself if present. Ignores all enqueue failures and does not stop when pair pool exhausted. No own insertion into common list, null/duplicate-pair/flag gate or cached-next protection. Nominal return is last visited pointer or preloop type/plane bits when empty, not uniform success/count. Pair rejection and flags belong to full filter delegate; global planes remain overwritten.
float *__cdecl rf_collision_register_object_against_active_list(int a1)
{
  float *result; // eax
  int i; // [esp+0h] [ebp-4h]

  result = (float *)a1;
  if ( *(_DWORD *)(a1 + 36) == 2 )
  {
    result = (float *)(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 616) & 0x20);
    if ( result )
      result = rf_collision_prepare_projectile_pair_planes(a1);
  }
  for ( i = unk_7D0C90; (_UNKNOWN *)i != &unk_7D0C80; i = *(_DWORD *)(i + 16) )
  {
    rf_collision_pair_try_enqueue(a1, i);
    result = (float *)i;
  }
  return result;
}

