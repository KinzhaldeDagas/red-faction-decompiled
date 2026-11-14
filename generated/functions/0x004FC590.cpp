// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC590 rf_event_holster_weapon_apply
// VERIFIED: Handler selected by event dispatch case 64, whose active event-type table entry is exactly 'Holster_Weapon'. For every resolved event target it sets owner +2064 bit 0x800 and AI-block +1328 bit 0x200, proving the latter is AI holstered-state storage.
// UNREALRED VERIFIED [weapon-events-20260826]: Event-table case 64 (Holster_Weapon). Iterates the common target identifier array at event +0x29C, resolves each target through the entity-only resolver, and skips unresolved or non-entity targets. Every resolved owner receives owner +0x810 bit 0x800 and owner +0x7D0 bit 0x200. It does not clear weapon ownership or the selected weapon indices.
int __cdecl rf_event_holster_weapon_apply(int a1)
{
  int result; // eax
  int *v2; // eax
  int v3; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(a1 + 668), i);
    v3 = rf_entity_resolve_handle(*v2);
    if ( v3 )
    {
      *(_DWORD *)(v3 + 2064) |= 0x800u;
      *(_DWORD *)(v3 + 2000) |= 0x200u;
    }
  }
  return result;
}

