// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004401C0 rf_entity_play_footstep_trigger
// UNREALRED VERIFIED [animation-trigger-decode]: Consumes left/right footstep triggers and selects the corresponding half of the authored sound-set variants.
void __cdecl rf_entity_play_footstep_trigger(int a1)
{
  int v1; // eax
  float v2; // [esp-14h] [ebp-44h] BYREF
  int v3; // [esp-10h] [ebp-40h]
  int v4; // [esp-Ch] [ebp-3Ch]
  int v5; // [esp-8h] [ebp-38h]
  int v6; // [esp-4h] [ebp-34h]
  float v7; // [esp+0h] [ebp-30h]
  float v8; // [esp+4h] [ebp-2Ch]
  float v9; // [esp+10h] [ebp-20h] BYREF
  float v10; // [esp+14h] [ebp-1Ch]
  int v11; // [esp+1Ch] [ebp-14h]
  float v12; // [esp+20h] [ebp-10h] BYREF
  float v13; // [esp+24h] [ebp-Ch]
  int v14; // [esp+2Ch] [ebp-4h]

  if ( *(_DWORD *)(a1 + 512) == -1 )
  {
    if ( sub_438AC0(a1) && !rf_view_wrapper_get_dword8(*(_DWORD *)(*(_DWORD *)(a1 + 5168) + 196)) )
    {
      rf_entity_emit_movement_foley_from_shared_distance(a1);
      return;
    }
    if ( (unsigned __int8)rf_character_trigger_query(*(_DWORD *)(a1 + 128), (int)"footstep_left") )
    {
      if ( *(int *)(*(_DWORD *)(a1 + 660) + 4 * *(_DWORD *)(a1 + 4992) + 376) < 0 )
      {
        if ( *(int *)(*(_DWORD *)(a1 + 660) + 376) < 0 )
          return;
        v14 = 0;
      }
      else
      {
        v14 = *(_DWORD *)(a1 + 4992);
      }
      rf_vector3_copy_return_destination(&v12, (float *)(a1 + 60));
      v13 = v13 - *(float *)(a1 + 384);
      v8 = unk_6E671C;
      v7 = 1.0;
      v6 = rf_foley_group_sound_count(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v14 + 376)) / 2;
      v5 = rf_foley_group_sound_array(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v14 + 376));
      rf_vector3_copy_return_destination(&v2, &v12);
      rf_sound_list_select_play_return_asset(a1, v2, v3, v4, v5, v6, v7, v8);
    }
    if ( !(unsigned __int8)rf_character_trigger_query(*(_DWORD *)(a1 + 128), (int)"footstep_right") )
      return;
    if ( *(int *)(*(_DWORD *)(a1 + 660) + 4 * *(_DWORD *)(a1 + 4992) + 376) >= 0 )
    {
      v14 = *(_DWORD *)(a1 + 4992);
LABEL_18:
      rf_vector3_copy_return_destination(&v9, (float *)(a1 + 60));
      v10 = v10 - *(float *)(a1 + 384);
      v11 = rf_foley_group_sound_array(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v14 + 376));
      v1 = rf_foley_group_sound_count(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v14 + 376));
      v11 += 4 * (v1 / 2);
      v8 = unk_6E671C;
      v7 = 1.0;
      v6 = rf_foley_group_sound_count(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 4 * v14 + 376)) / 2;
      v5 = v11;
      rf_vector3_copy_return_destination(&v2, &v9);
      rf_sound_list_select_play_return_asset(a1, v2, v3, v4, v5, v6, v7, v8);
      return;
    }
    if ( *(int *)(*(_DWORD *)(a1 + 660) + 376) >= 0 )
    {
      v14 = 0;
      goto LABEL_18;
    }
  }
}

