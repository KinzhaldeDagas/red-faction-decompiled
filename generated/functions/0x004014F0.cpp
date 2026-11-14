// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004014F0 sub_4014F0
// UNREALRED VERIFIED [combat-fire-exhaustion-20260930] Eight-entry rows at 0x661018 are indexed by record+0x24, where Entity+0x147C selects a stride-0x54 record at 0x757668. No record (-1) selects ID3 without ownership/ammo checks. Forced calls bypass rand()%8 admission; no eligible candidate retains the current selection. A missing current selection first invokes ID3 grant/init at 0x4013A0. This is separate from player preferences.
// UNREALRED VERIFIED [combat-selector-owner-20260930] For Entity+0x147C == -1, forced recovery assigns selected weapon ID3 without checking ownership or ammunition and without granting. If already ID3 it returns false. Ordinary entity construction initializes this record index to -1. Do not replace this branch with an archetype grant or player preference selection.
// UNREALRED VERIFIED [combat-reaction-20261111]: The no-player-record Entity+147C==-1 branch selects ID3 without an ownership/ammo test or grant (apart from the earlier distinct current-primary==-1 initialization). Final stop-firing/write/holding refresh changes selected primary AI+4 only; AI+8 secondary is not rewritten. A host inventory index of-1 cannot alone prove native primary selection is-1.
// UNREALRED VERIFIED [combat-ammo-identity-20261111]: Forced new-ownership callback first tests43BFF0. If currentprimary==-1 invokes4013A0(write3 then grant3). Only AFTER that initialization and optional rand gate does no-player-record Entity147C==-1 choose3 withoutownership/ammo/grant. Constructor grant chains can therefore acquireID3 as well as authoreddefaults. Preserveinitialization vs selection-only distinction; secondary remains independent.
char __cdecl sub_4014F0(int *a1, char a2)
{
  unsigned int v3; // [esp+4h] [ebp-10h]
  int v4; // [esp+Ch] [ebp-8h]
  int i; // [esp+10h] [ebp-4h]

  v4 = -1;
  if ( !sub_43BFF0(*a1) )
    return 0;
  if ( a1[1] == -1 )
    sub_4013A0(a1);
  if ( !a2 && rand() % 8 )
    return 0;
  for ( i = 0; i < 8; ++i )
  {
    if ( *(_DWORD *)(*a1 + 5244) == -1 )
    {
      v4 = 3;
    }
    else
    {
      v3 = dword_661018[8 * unk_75768C[21 * *(_DWORD *)(*a1 + 5244)] + i];
      if ( sub_403D00((int)a1, v3) && sub_401470((int)a1, v3) )
      {
        v4 = v3;
        break;
      }
    }
  }
  if ( a1[1] == v4 )
    return 0;
  if ( v4 == -1 )
  {
    if ( !a2 )
      return sub_4014F0(a1, 1);
  }
  else
  {
    rf_entity_stop_weapon_firing(*(_DWORD *)(*a1 + 44), a1[1]);
    a1[1] = v4;
    rf_entity_restore_action_tables_and_apply_weapon_overrides(*a1, a1[1]);
  }
  return v4 != -1;
}

