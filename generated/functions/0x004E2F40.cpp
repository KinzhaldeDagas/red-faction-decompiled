// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E2F40 rf_vehicle_update_apc_fighter_cockpit_materials
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Cdecl(entity,material count,table pointer). Fighter class mask0x800 nonzero loads fighter digit/bank assets and chooses digits662EFC; otherwise loads APC assets and digits662E4C. Always computes life gauge using APC framecount87C6B8, primary/secondary RAW ammo gauges using87C6BC/C0, including fighter path; fighter loader does not load those APC gauge bases/counts. Loop signed i<count, stride200; exact case-sensitive NUL-terminated filename at+20, writes bitmap handle+16 only for matching names. cockpit_armor/primary/secondary.tga -> gauge offsets +bases662E60/74/88. Original misspelling cocpit_armor_digit1..3.tga -> life digits multipliersF32 .01,.1,1; cocpit_primary_digit1..4.tga -> raw primary reserve .001,.01,.1,1; cocpit_second_digit1..3.tga
// -> raw secondary reserve .01,.1,1. Each digit adds helper3C40 offset to selected digit base. Fighter bank offsets startL=R=2; timer entity+1212 must return AL EXACT1 and safe secondary-weapon(entity+680) reserve query nonzero: entity+1292 nonzero setsL1, zero setsR1. Fighter-only cocpit_armor_L_Bank/R_Bank.tga assign bank bases662F50/68 plus these offsets after common filename chain. Unknown names/other fields unchanged. Assets/gauges computed even count<=0; no capacity/finite/weapon-index checks. EAX count after positive loop, incidental helper residue for nonpositive count, not reliable success.
void __cdecl rf_vehicle_update_apc_fighter_cockpit_materials(int *entity, int a2, int a3)
{
  int v3; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  int v11; // eax
  int v12; // eax
  int raw_reserve; // [esp+130h] [ebp-28h] BYREF
  int v14; // [esp+134h] [ebp-24h] BYREF
  int frame_offset; // [esp+138h] [ebp-20h] BYREF
  int v16; // [esp+13Ch] [ebp-1Ch] BYREF
  int v17; // [esp+140h] [ebp-18h] BYREF
  int v18; // [esp+144h] [ebp-14h]
  int v19; // [esp+148h] [ebp-10h] BYREF
  int i; // [esp+14Ch] [ebp-Ch]
  int v21; // [esp+150h] [ebp-8h]
  int v22; // [esp+154h] [ebp-4h]

  v18 = 2;
  v21 = 2;
  if ( rf_entity_class_flags724_has_mask800((int)entity) )
  {
    rf_fighter_cockpit_load_digit_and_bank_bitmaps();
    v22 = dword_662EFC;
    if ( rf_replicator_has_elapsed(entity + 303) && sub_4391D0((int)entity, entity[170]) )
    {
      if ( entity[323] )
        v18 = 1;
      else
        v21 = 1;
    }
  }
  else
  {
    rf_apc_cockpit_load_gauge_and_digit_bitmaps();
    v22 = dword_662E4C;
  }
  rf_cockpit_get_life_gauge_frame_and_integer((int)entity, unk_87C6B8, &v19, &v14);
  rf_cockpit_get_primary_reserve_gauge((int)entity, dword_87C6BC, &frame_offset, &raw_reserve);
  rf_cockpit_get_secondary_reserve_gauge((int)entity, dword_87C6C0, &v16, &v17);
  for ( i = 0; i < a2; ++i )
  {
    if ( !strcmp((const char *)(a3 + 200 * i + 20), "cockpit_armor.tga") )
    {
      *(_DWORD *)(a3 + 200 * i + 16) = v19 + dword_662E60;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cockpit_primary.tga") )
    {
      *(_DWORD *)(a3 + 200 * i + 16) = frame_offset + dword_662E74;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cockpit_secondary.tga") )
    {
      *(_DWORD *)(a3 + 200 * i + 16) = v16 + dword_662E88;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_armor_digit1.tga") )
    {
      v3 = rf_cockpit_digit_frame_offset(v14, 0.0099999998);
      *(_DWORD *)(a3 + 200 * i + 16) = v22 + v3;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_armor_digit2.tga") )
    {
      v4 = rf_cockpit_digit_frame_offset(v14, 0.1);
      *(_DWORD *)(a3 + 200 * i + 16) = v22 + v4;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_armor_digit3.tga") )
    {
      v5 = rf_cockpit_digit_frame_offset(v14, 1.0);
      *(_DWORD *)(a3 + 200 * i + 16) = v22 + v5;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_primary_digit1.tga") )
    {
      v6 = rf_cockpit_digit_frame_offset(raw_reserve, 0.001);
      *(_DWORD *)(a3 + 200 * i + 16) = v22 + v6;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_primary_digit2.tga") )
    {
      v7 = rf_cockpit_digit_frame_offset(raw_reserve, 0.0099999998);
      *(_DWORD *)(a3 + 200 * i + 16) = v22 + v7;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_primary_digit3.tga") )
    {
      v8 = rf_cockpit_digit_frame_offset(raw_reserve, 0.1);
      *(_DWORD *)(a3 + 200 * i + 16) = v22 + v8;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_primary_digit4.tga") )
    {
      v9 = rf_cockpit_digit_frame_offset(raw_reserve, 1.0);
      *(_DWORD *)(a3 + 200 * i + 16) = v22 + v9;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_second_digit1.tga") )
    {
      v10 = rf_cockpit_digit_frame_offset(v17, 0.0099999998);
      *(_DWORD *)(a3 + 200 * i + 16) = v22 + v10;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_second_digit2.tga") )
    {
      v11 = rf_cockpit_digit_frame_offset(v17, 0.1);
      *(_DWORD *)(a3 + 200 * i + 16) = v22 + v11;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_second_digit3.tga") )
    {
      v12 = rf_cockpit_digit_frame_offset(v17, 1.0);
      *(_DWORD *)(a3 + 200 * i + 16) = v22 + v12;
    }
    if ( rf_entity_class_flags724_has_mask800((int)entity) )
    {
      if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_armor_L_Bank.tga") )
      {
        *(_DWORD *)(a3 + 200 * i + 16) = v18 + dword_662F50;
      }
      else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_armor_R_Bank.tga") )
      {
        *(_DWORD *)(a3 + 200 * i + 16) = v21 + dword_662F68;
      }
    }
  }
}

