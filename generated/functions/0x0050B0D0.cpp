// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0050B0D0 rf_projectile_contact_response_dispatch
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, weapon contact/decal control flow,ammo registry,rail trail pool,constructor layout and native argument/return ABI,original ECX/stack flow and PE bytes): Thiscall projectile, no stack arguments; returns response codes0/1/2, not simple bool. Unchecked-normalizes collision normal+448 FIRST. Liquid indicator DWORD+492 nonzero calls50B4D0, sets trail flags+760 bit4; if prior bit1 set, clears bit2/sets bit8 and copies collision point+436 to+764; otherwise sets bit2 and copies point to BOTH+764/+108. Info flags+612 mask800h also zeros thrust remaining+756 in liquid branch. Otherwise only ORDERED F32+468==0 selects world-contact50B590; all nonzero and NaN select object-contact50C340. World path captures point+764 only if bit8 was clear; object path always sets bit8/captures point. If selected handler AL is NONZERO: info
// mask01000000 makes liquid clear physics+428 mask1000h and liquid+492 then return1, but nonliquid returns0 WITHOUT deletion. Without that mask clears liquid state if present then returns2 only for grenade with projectile flags+680 bit10h clear; otherwise1. Handler AL zero ALWAYS marks deferred deletion; no object/light free. Terminal shoulder cannon additionally scans local players, resolves entity+20, forms unit direction from entity point+2004 to projectile position+60 and F32 Euclidean distance D, dot V against entity+2040. Only ORDERED D<DOUBLE33.29999923706055 applies view impulse4123F0(player+196,0.003f,1.25f); computed1-D/33.3 afterward is unused. ORDERED D<50 applies HUD tint RGB255,255,192: V<0 OR UNORDERED =>alpha32; otherwise alpha=FTOL((V+V)*F32(1-D/50)*DOUBLE255)+32, upper-clamped255 only. Returns0 after terminal path. No distance/normal finite guards, LOS/team filtering or
// unconditional cleanup implied by response0.
int __thiscall rf_projectile_contact_response_dispatch(int this)
{
  float *v1; // eax
  float v4[3]; // [esp+Ch] [ebp-6Ch] BYREF
  float v5[3]; // [esp+18h] [ebp-60h] BYREF
  float v6[3]; // [esp+24h] [ebp-54h] BYREF
  float v7[3]; // [esp+30h] [ebp-48h] BYREF
  float copy_result[3]; // [esp+3Ch] [ebp-3Ch] BYREF
  float v9; // [esp+48h] [ebp-30h]
  int v10; // [esp+4Ch] [ebp-2Ch]
  float v11; // [esp+50h] [ebp-28h]
  float out_vector[3]; // [esp+54h] [ebp-24h] BYREF
  float v13; // [esp+60h] [ebp-18h]
  float v14; // [esp+64h] [ebp-14h]
  int v15; // [esp+68h] [ebp-10h]
  int v16; // [esp+6Ch] [ebp-Ch]
  int i; // [esp+70h] [ebp-8h]
  char v18; // [esp+77h] [ebp-1h]

  rf_vector_normalize_reciprocal_sqrt((float *)(this + 448));
  if ( *(_DWORD *)(this + 492) )
  {
    v18 = sub_50B4D0(this);
    *(_DWORD *)(this + 760) |= 4u;
    if ( (*(_DWORD *)(this + 760) & 1) != 0 )
    {
      *(_DWORD *)(this + 760) &= ~2u;
      *(_DWORD *)(this + 760) |= 8u;
      rf_vector_copy((float *)(this + 764), copy_result, (const float *)(this + 436));
    }
    else
    {
      *(_DWORD *)(this + 760) |= 2u;
      v1 = rf_vector_copy((float *)(this + 764), v7, (const float *)(this + 436));
      rf_vector_copy((float *)(this + 108), v6, v1);
    }
    if ( (*(_DWORD *)(*(_DWORD *)(this + 660) + 612) & 0x800) != 0 )
      *(float *)(this + 756) = 0.0;
  }
  else if ( *(float *)(this + 468) == 0.0 )
  {
    v18 = rf_projectile_world_contact_response(this);
    if ( (*(_DWORD *)(this + 760) & 8) == 0 )
    {
      *(_DWORD *)(this + 760) |= 8u;
      rf_vector_copy((float *)(this + 764), v5, (const float *)(this + 436));
    }
  }
  else
  {
    v18 = rf_projectile_object_contact(this);
    *(_DWORD *)(this + 760) |= 8u;
    rf_vector_copy((float *)(this + 764), v4, (const float *)(this + 436));
  }
  if ( v18 )
  {
    if ( ((unsigned int)&unk_1000000 & *(_DWORD *)(*(_DWORD *)(this + 660) + 612)) != 0 )
    {
      if ( *(_DWORD *)(this + 492) )
      {
        *(_DWORD *)(this + 428) &= ~0x1000u;
        *(_DWORD *)(this + 492) = 0;
        return 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      if ( *(_DWORD *)(this + 492) )
      {
        *(_DWORD *)(this + 428) &= ~0x1000u;
        *(_DWORD *)(this + 492) = 0;
      }
      if ( *(_DWORD *)(this + 664) != rf_weapon_index_grenade || (*(_DWORD *)(this + 680) & 0x10) != 0 )
        return 1;
      else
        return 2;
    }
  }
  else
  {
    rf_object_mark_for_deferred_delete(this);
    if ( *(_DWORD *)(this + 664) == rf_weapon_id_shoulder_cannon )
    {
      for ( i = 0; i < rf_local_player_entry_count; ++i )
      {
        v15 = rf_local_player_entries[i];
        v16 = rf_entity_resolve_handle(*(_DWORD *)(v15 + 20));
        if ( v16 )
        {
          rf_vector_subtract((const float *)(this + 60), out_vector, (const float *)(v16 + 2004));
          v13 = rf_vector3_normalize_return_length(out_vector);
          v14 = rf_vector_dot((float *)(v16 + 2040), out_vector);
          if ( v13 < 33.29999923706055 )
          {
            rf_entity_set_player_linked_perturbation_timer(*(_DWORD *)(v15 + 196), 0.003, 1.25);
            v11 = 1.0 - v13 / 33.29999923706055;
          }
          if ( v13 < 50.0 )
          {
            v9 = 1.0 - v13 / 50.0;
            if ( v14 < 0.0 )
            {
              v10 = 32;
            }
            else
            {
              v10 = (int)((v14 + v14) * v9 * 255.0) + 32;
              if ( v10 > 255 )
                v10 = 255;
            }
            rf_player_hud_screen_tint_set(v15, 255, 255, 192, v10);
          }
        }
      }
    }
    return 0;
  }
}

