// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0040BE80 rf_ai_spawn_elapsed_projectiles
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI/corpse-carry/inventory/projectile update chains, original field layouts and float constants and native
// signed/x87/stack/callback ABI): One required AI block, entity DWORD+0 and signed weapon index+4. Only0<=weapon<911C68 and438AC0(entity) AL!=EXACT1 admit. For slots0/1 at block
// deadlines+544/+548, elapsed EXACT AL1 resets deadline BEFORE spawning; both can spawn same update. Weapon records have1360-byte stride; flags DWORD+612 mask0x400 selects copied
// entity orientation+2016 and spawn position entity+2004. For grenade in that branch, initializes direction from local matrix row2 (forward); local matrix at EBP-0x30 has row1
// EBP-0x24 (up) and row2 EBP-0x18, despite pseudocode splitting them into independent arrays. Resolves target full handle block+704; miss exits ENTIRE function after consuming
// current deadline, so later slot is not processed. Horizontal distance d=float32(float32(abs(targetX-entityX))+float32(abs(targetZ-entityZ))). Ordered d>DOUBLE30 gives factor1;
// ordered d<DOUBLE3 gives5; else including NaN uses float32(34/(d+4)). Factor then rounded after*(1+(rand()%9-4)/DOUBLE16). Direction becomes normalized(forward+up/factor), then
// constructs spawn matrix. Other weapons in mask0x400 branch use unmodified copied matrix. No mask0x400:422CC0(entity,weapon,tempPosition,tempMatrix,block DWORD+624,1), ignored
// result; class flags(+660)->+1832 mask0x20 chooses tempMatrix, else entity+2016, always tempPosition. Projectile creator receives exactly six stack args(weapon,entity
// handle+44,position,matrix,0,0). Successful grenade with entity player pointer+5168==0 gets projectile DWORD+680 OR0x10. No own multiplayer/authority test, ammo consumption or
// direct damage; EAX/AL is incidental across many paths, not a spawn-success boolean.
char __cdecl rf_ai_spawn_elapsed_projectiles(int *a1)
{
  int runtime; // eax
  float *v2; // eax
  float v4; // [esp+8h] [ebp-98h]
  float v5; // [esp+Ch] [ebp-94h]
  int v6[3]; // [esp+10h] [ebp-90h] BYREF
  float copy_result[3]; // [esp+1Ch] [ebp-84h] BYREF
  char v8[36]; // [esp+28h] [ebp-78h] BYREF
  _BYTE v9[12]; // [esp+4Ch] [ebp-54h] BYREF
  float destination[3]; // [esp+58h] [ebp-48h] BYREF
  int v11; // [esp+64h] [ebp-3Ch]
  float v12; // [esp+68h] [ebp-38h]
  float v13; // [esp+6Ch] [ebp-34h]
  float v14[3]; // [esp+70h] [ebp-30h] BYREF
  float v15[3]; // [esp+7Ch] [ebp-24h] BYREF
  float source[3]; // [esp+88h] [ebp-18h] BYREF
  int v17; // [esp+94h] [ebp-Ch]
  char *v18; // [esp+98h] [ebp-8h]
  int i; // [esp+9Ch] [ebp-4h]

  LOBYTE(runtime) = (_BYTE)a1;
  if ( a1[1] >= 0 && a1[1] < dword_911C68 )
  {
    LOBYTE(runtime) = sub_438AC0(*a1);
    if ( (unsigned __int8)runtime != 1 )
    {
      LOBYTE(runtime) = (_BYTE)a1;
      v18 = (char *)&rf_weapon_records + 1360 * a1[1];
      for ( i = 0; i < 2; ++i )
      {
        LOBYTE(runtime) = rf_replicator_has_elapsed(&a1[i + 136]);
        if ( (unsigned __int8)runtime == 1 )
        {
          rf_replicator_reset(&a1[i + 136]);
          if ( (*((_DWORD *)v18 + 153) & 0x400) != 0 )
          {
            rf_matrix3_construct((char *)v14);
            rf_matrix3_copy(v14, (const float *)(*a1 + 2016));
            if ( a1[1] == rf_weapon_index_grenade )
            {
              rf_vector3_default_construct_noop(destination);
              rf_vector_copy(destination, copy_result, source);
              runtime = rf_object_resolve_handle(a1[176]);
              v11 = runtime;
              if ( !runtime )
                return runtime;
              v5 = fabs(*(float *)(v11 + 60) - *(float *)(*a1 + 60));
              v4 = fabs(*(float *)(v11 + 68) - *(float *)(*a1 + 68));
              v12 = v5 + v4;
              if ( v12 <= 30.0 )
              {
                if ( v12 >= 3.0 )
                  v13 = 34.0 / (v12 + 4.0);
                else
                  v13 = 5.0;
              }
              else
              {
                v13 = 1.0;
              }
              v13 = ((double)(rand() % 9 - 4) / 16.0 + 1.0) * v13;
              v2 = rf_vector_divide(v15, (float *)v6, v13);
              rf_vector_accumulate(destination, v2);
              rf_vector_normalize_reciprocal_sqrt(destination);
              rf_orientation_matrix_from_normalized_direction(v14, destination);
            }
            runtime = rf_projectile_create_runtime(a1[1], *(_DWORD *)(*a1 + 44), *a1 + 2004, (int)v14, 0, 0);
            v17 = runtime;
          }
          else
          {
            rf_vector3_default_construct_noop(v9);
            rf_matrix3_construct(v8);
            rf_entity_resolve_firing_transform((_DWORD *)*a1, a1[1], (int)v9, (int)v8, a1[156], 1);
            if ( (*(_DWORD *)(*(_DWORD *)(*a1 + 660) + 1832) & 0x20) != 0 )
              runtime = rf_projectile_create_runtime(a1[1], *(_DWORD *)(*a1 + 44), (int)v9, (int)v8, 0, 0);
            else
              runtime = rf_projectile_create_runtime(a1[1], *(_DWORD *)(*a1 + 44), (int)v9, *a1 + 2016, 0, 0);
            v17 = runtime;
          }
          if ( v17 )
          {
            LOBYTE(runtime) = v17;
            if ( *(_DWORD *)(v17 + 664) == rf_weapon_index_grenade )
            {
              runtime = *a1;
              if ( !*(_DWORD *)(*a1 + 5168) )
              {
                LOBYTE(runtime) = v17;
                *(_DWORD *)(v17 + 680) |= 0x10u;
              }
            }
          }
        }
      }
    }
  }
  return runtime;
}

