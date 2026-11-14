// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491400 sub_491400
// UNREALRED VERIFIED [combat-fire-exhaustion-20260930] First-free allocation among 16 records of stride0x54 at 0x757668 stores the entity pointer at+0x20, writes the slot into Entity+0x147C, and initializes record+0x24 from 0x6628D0[slot] (pinned image values0..15). This establishes selector row ownership. Raw registration caller0x491610 is code outside a defined function in the current database; its broader reachability is not asserted here.
int __cdecl sub_491400(int a1)
{
  int result; // eax
  int *v2; // [esp+8h] [ebp-8h]
  int i; // [esp+Ch] [ebp-4h]

  for ( i = 0; i < 16; ++i )
  {
    if ( !unk_757668[21 * i] )
    {
      v2 = &unk_757668[21 * i];
      *v2 = 1;
      v2[8] = a1;
      v2[1] = 0;
      v2[3] = 0;
      v2[4] = 0;
      v2[5] = 0;
      v2[6] = 0;
      v2[7] = 0;
      *(_DWORD *)(a1 + 5244) = i;
      *(_DWORD *)(a1 + 2064) |= 0x100000u;
      v2[9] = dword_6628D0[i];
      v2[10] = *(_DWORD *)(a1 + 1316);
      v2[11] = *(_DWORD *)(a1 + 1368);
      v2[12] = *(_DWORD *)(a1 + 1864);
      v2[13] = *(_DWORD *)(a1 + 1868);
      *((_BYTE *)v2 + 56) = *(_BYTE *)(a1 + 1992);
      v2[15] = *(int *)(a1 + 1996);
      v2[16] = *(_DWORD *)(a1 + 1308);
      v2[17] = *(_DWORD *)(a1 + 1856);
      v2[18] = *(int *)(a1 + 52);
      v2[19] = *(int *)(a1 + 56);
      break;
    }
  }
  result = rf_splitscreen_runtime_active;
  if ( rf_splitscreen_runtime_active )
  {
    result = (int)rf_splitscreen_get_settings_storage();
    if ( !*(_BYTE *)(result + 16) )
      return rf_entity_clear_weapon_inventory(a1);
  }
  return result;
}

