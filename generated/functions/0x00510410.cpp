// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00510410 rf_projectile_try_play_near_miss_sound
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, projectile lifetime and attachments,weapon selectors,near-miss unordered branches,model and animation caches,original ECX/stack flow and PE bytes): Arguments target object, projectile, sound-position pointer. Resolves projectile owner UID+48 to entity; missing owner or melee weapon predicate==1 returns AL0. Rejects ONLY ORDERED info F32+192<100. Uses F32 FAST distances from shooter remembered point+1380 to target+60 (D) and shooter position+60 to target (S); shooter flags+2068 bit4 forces S=10. Rejects ONLY ORDERED S<3. D>=2 OR UNORDERED updates remembered point/timestamp through40BBD0(shooter+672,target+60), penalty=0. Otherwise elapsedSec=F32(signed elapsed1392/DOUBLE1000); numerator=F32(elapsedSec squared), denominator argument=F32((D+DOUBLE1)*S), penalty=F32(numerator/sqrt_float(denominator)). Draws CRT
// rand()/DOUBLE32767: requires ORDERED difficulty probability661264[6612A4]>first draw. Only then draws again; rejects ONLY ORDERED penalty>second draw (unordered penalty passes). Predicate5119A0 selects info+500 ($Near Miss Underwater), else+496 ($Near Miss Sound); chooses foley sound then positional play at supplied position, volume1, vector17F10B0, final0. AL1 means play attempted, not successful. Remembered point may update before later probability rejection. No damage, impact Vclip spawn, target/projectile/info NULL guards or difficulty bounds. Native AH5/JP and AH41/JNZ branches govern NaN behavior beyond pseudocode.
char __cdecl rf_projectile_try_play_near_miss_sound(int a1, _DWORD *a2, float *a3)
{
  int v4; // eax
  float v5; // [esp+1Ch] [ebp-1Ch]
  float v6; // [esp+24h] [ebp-14h]
  float v7; // [esp+28h] [ebp-10h]
  float v8; // [esp+2Ch] [ebp-Ch]
  int v9; // [esp+30h] [ebp-8h]
  float v10; // [esp+34h] [ebp-4h]

  v9 = rf_entity_resolve_handle(a2[12]);
  if ( !v9 )
    return 0;
  if ( rf_weapon_is_melee(a2[166]) )
    return 0;
  if ( *(float *)(a2[165] + 192) < 100.0 )
    return 0;
  v7 = rf_vector_fast_distance((const float *)(v9 + 1380), (const float *)(a1 + 60));
  v8 = rf_vector_fast_distance((const float *)(v9 + 60), (const float *)(a1 + 60));
  v10 = 0.0;
  if ( (*(_DWORD *)(v9 + 2068) & 4) != 0 )
    v8 = 10.0;
  if ( v8 < 3.0 )
    return 0;
  if ( v7 >= 2.0 )
  {
    rf_ai_store_target_position_and_arm_zero_deadline(v9 + 672, (float *)(a1 + 60));
  }
  else
  {
    v6 = (double)rf_timestamp_signed_elapsed_milliseconds((void *)(v9 + 1392)) / 1000.0;
    v5 = (v7 + 1.0) * v8;
    v10 = v6 * v6 / rf_sqrt_float(v5);
  }
  if ( flt_661264[dword_6612A4] <= (double)rand() / 32767.0 )
    return 0;
  if ( v10 > (double)rand() / 32767.0 )
    return 0;
  if ( rf_projectile_flag2_damage_type_is_1_or_2((int)a2) )
    v4 = rf_foley_choose_random_sound(*(_DWORD *)(a2[165] + 500));
  else
    v4 = rf_foley_choose_random_sound(*(_DWORD *)(a2[165] + 496));
  rf_gamesound_play_positional_event(v4, a3, 1.0, (int)flt_17F10B0, 0);
  return 1;
}

