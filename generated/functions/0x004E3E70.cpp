// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E3E70 rf_vehicle_update_submarine_cockpit_materials
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Cdecl(entity,material count,table). Lazy-load sub assets, compute LIFE gauge/frame using87C6C4 and class-primary RAW reserve gauge using87C6C8. BankL/R default2; timer entity+1208 AL EXACT1 AND selected-primary wrapping total ammo436310 NONZERO: entity+1296==1 setsR1, all other values setL1. Negative nonzero total also admits bank indicator. Signed loop i<count over200-byte material records, exact case-sensitive NUL filename+20 writes bitmap+16: cockpit_armor.tga ->662EB4+life frame; cockpit_primary.tga ->662EC8+reserve frame; cocpit_armor_digit1..3.tga ->662EA0+life decimal frame(.01,.1,1); cocpit_primary_digit1..3.tga ->662EA0+raw reserve decimal frame(.01,.1,1); cocpit_armor_L_Bank/R_Bank.tga ->662EE8/EF8+bank offsets. Original cocpit spelling
// significant. Unknown names/other bytes unchanged; no secondary gauge. Preloads and gauge arithmetic run even count<=0. Returns final loop index(count when positive,otherwise0), not changed-material count/status.
int __cdecl rf_vehicle_update_submarine_cockpit_materials(int entity, int a2, int a3)
{
  int result; // eax
  int v4; // eax
  int v5; // eax
  int v6; // eax
  int v7; // eax
  int v8; // eax
  int v9; // eax
  int raw_reserve; // [esp+CCh] [ebp-1Ch] BYREF
  int v11; // [esp+D0h] [ebp-18h] BYREF
  int frame_offset; // [esp+D4h] [ebp-14h] BYREF
  int v13; // [esp+D8h] [ebp-10h] BYREF
  int v14; // [esp+DCh] [ebp-Ch]
  int i; // [esp+E0h] [ebp-8h]
  int v16; // [esp+E4h] [ebp-4h]

  rf_submarine_cockpit_load_gauge_digit_and_bank_bitmaps();
  rf_cockpit_get_life_gauge_frame_and_integer(entity, unk_87C6C4, &v13, &v11);
  rf_cockpit_get_primary_reserve_gauge(entity, dword_87C6C8, &frame_offset, &raw_reserve);
  v14 = 2;
  v16 = 2;
  if ( rf_replicator_has_elapsed((int *)(entity + 1208)) && sub_436310(entity) )
  {
    if ( *(_DWORD *)(entity + 1296) == 1 )
      v16 = 1;
    else
      v14 = 1;
  }
  for ( i = 0; ; ++i )
  {
    result = i;
    if ( i >= a2 )
      break;
    if ( !strcmp((const char *)(a3 + 200 * i + 20), "cockpit_armor.tga") )
    {
      *(_DWORD *)(a3 + 200 * i + 16) = v13 + dword_662EB4;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cockpit_primary.tga") )
    {
      *(_DWORD *)(a3 + 200 * i + 16) = frame_offset + dword_662EC8;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_armor_digit1.tga") )
    {
      v4 = rf_cockpit_digit_frame_offset(v11, 0.0099999998);
      *(_DWORD *)(a3 + 200 * i + 16) = dword_662EA0 + v4;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_armor_digit2.tga") )
    {
      v5 = rf_cockpit_digit_frame_offset(v11, 0.1);
      *(_DWORD *)(a3 + 200 * i + 16) = dword_662EA0 + v5;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_armor_digit3.tga") )
    {
      v6 = rf_cockpit_digit_frame_offset(v11, 1.0);
      *(_DWORD *)(a3 + 200 * i + 16) = dword_662EA0 + v6;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_primary_digit1.tga") )
    {
      v7 = rf_cockpit_digit_frame_offset(raw_reserve, 0.0099999998);
      *(_DWORD *)(a3 + 200 * i + 16) = dword_662EA0 + v7;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_primary_digit2.tga") )
    {
      v8 = rf_cockpit_digit_frame_offset(raw_reserve, 0.1);
      *(_DWORD *)(a3 + 200 * i + 16) = dword_662EA0 + v8;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_primary_digit3.tga") )
    {
      v9 = rf_cockpit_digit_frame_offset(raw_reserve, 1.0);
      *(_DWORD *)(a3 + 200 * i + 16) = dword_662EA0 + v9;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_armor_L_Bank.tga") )
    {
      *(_DWORD *)(a3 + 200 * i + 16) = v14 + dword_662EE8;
    }
    else if ( !strcmp((const char *)(a3 + 200 * i + 20), "cocpit_armor_R_Bank.tga") )
    {
      *(_DWORD *)(a3 + 200 * i + 16) = v16 + dword_662EF8;
    }
  }
  return result;
}

