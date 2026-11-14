// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00488B30 rf_mover_update_linked_pickups
// UNREALRED VERIFIED [mission-mover-runtime-20261013] Updates PICKUP availability, not portal flags. Always reads FIRST key integer fields +0x4C/+0x50; resolves each via item UID lookup0x474620. Clears item+0x2BC bit1 while moving forward, sets it otherwise. Key arrival event UID is the separate +0x48 field. Binding0x48AC40 initially sets this pickup-disable bit. Item pickup0x473940 checks it before granting anything.
// UNREALRED VERIFIED [mission-mover-effects-20261013] Collection gate updates first-key linked item UIDs in order. Forward clears item flags+0x2BC bit1; backward sets it. No item visibility, respawn deadline or inventory grant is changed in this helper. Key-event dispatch precedes these updates in the linear arrival path.
int __cdecl rf_mover_update_linked_pickups(int a1)
{
  int result; // eax
  _DWORD *v2; // eax
  unsigned int v3; // ecx
  int v4; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  result = rf_receiver_get_first_dword((void *)(a1 + 668));
  if ( result > 0 )
  {
    for ( i = 0; i < 2; ++i )
    {
      v2 = (_DWORD *)sub_552200((_DWORD *)(a1 + 668), 0);
      v4 = rf_item_find_by_uid(*(_DWORD *)(*v2 + 4 * i + 76));
      if ( v4 )
      {
        if ( (*(_DWORD *)(a1 + 792) & 0x2000) != 0 )
          v3 = *(_DWORD *)(v4 + 700) & 0xFFFFFFFE;
        else
          v3 = *(_DWORD *)(v4 + 700) | 1;
        *(_DWORD *)(v4 + 700) = v3;
      }
      result = i + 1;
    }
  }
  return result;
}

