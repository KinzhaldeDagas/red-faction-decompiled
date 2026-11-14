// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00479EC0 sub_479EC0
// UNREALRED VERIFIED [trigger-airlock-20261022] Resolves authored room UID against loaded room owners. Airlock admission uses this lookup; authored room airlock flag+67 is not an additional admission requirement.
int __cdecl sub_479EC0(int a1)
{
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword((void *)(rf_world_solid + 156)); ++i )
  {
    v2 = *(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 156), i);
    if ( *(_DWORD *)(v2 + 36) == a1 )
      return v2;
  }
  return 0;
}

