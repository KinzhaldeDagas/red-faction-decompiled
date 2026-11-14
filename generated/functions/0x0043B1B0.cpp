// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043B1B0 rf_entity_consume_player_weapon_ammo_after_fire
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity fire actions, shared definitions and burn/debug records, Foley input, local-player controls and
// auxiliary view/render state and native signed/x87/stack/callback ABI): Cdecl(entity,weaponIndex,BYTE allowRiotDrain). First calls player-flag predicate4BB430; ANY nonzero AL
// admits. Exact weapon-1 and exact mutable global911C80 are excluded. Weapon equal runtime Riot Stick911C94 is excluded only when third BYTE is0; every other byte admits. Next exact
// flamethrower911CAC takes precedence: stores DWORD912088[1360*weapon] into entity loaded-ammo DWORD812+4*weapon, then subtracts a newly read table amount from reserve
// DWORD684+4*DWORD912024[1360*weapon], re-reading AmmoID for the final store. Other non-Riot weapons subtract1 from that unchecked reserve pool; admitted Riot Stick subtracts1 from
// loaded812+4*weapon instead. All arithmetic wraps32 and stores without floor, sufficiency/ownership/capacity/index/AmmoID checks; negative amounts can add reserve, and AmmoID-1
// addresses entity680. Entity pointer is not guarded by this body before the delegated predicate. No reload/animation/fire admission or network operation here. EAX/AL is
// branch-dependent residue, not a normalized success or remaining-ammo return.
char __cdecl rf_entity_consume_player_weapon_ammo_after_fire(int a1, int a2, char a3)
{
  int v3; // eax

  LOBYTE(v3) = rf_object_has_player_flag(a1);
  if ( (_BYTE)v3 )
  {
    if ( a2 != -1 )
    {
      LOBYTE(v3) = a2;
      if ( a2 != unk_911C80 && (a2 != rf_weapon_id_riot_stick || a3) )
      {
        if ( a2 == rf_weapon_id_flamethrower )
        {
          *(_DWORD *)(a1 + 4 * a2 + 812) = unk_912088[340 * a2];
          v3 = *(_DWORD *)(a1 + 4 * dword_912024[340 * a2] + 684) - unk_912088[340 * a2];
          *(_DWORD *)(a1 + 4 * dword_912024[340 * a2] + 684) = v3;
        }
        else if ( a2 == rf_weapon_id_riot_stick )
        {
          --*(_DWORD *)(a1 + 4 * a2 + 812);
          LOBYTE(v3) = a1;
        }
        else
        {
          v3 = *(_DWORD *)(a1 + 4 * dword_912024[340 * a2] + 684) - 1;
          *(_DWORD *)(a1 + 4 * dword_912024[340 * a2] + 684) = v3;
        }
      }
    }
  }
  return v3;
}

