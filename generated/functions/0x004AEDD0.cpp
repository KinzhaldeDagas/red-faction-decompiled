// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004AEDD0 rf_splitscreen_player_entity_create
// UNREALRED VERIFIED [weapon-holding-variants] Creates and initializes the gameplay entity owned by one split-screen Player record before viewport assignment.
float *__cdecl rf_splitscreen_player_entity_create(int a1)
{
  int first_dword; // eax
  float *v3; // [esp+0h] [ebp-34h]
  float v4[9]; // [esp+4h] [ebp-30h] BYREF
  float v5[3]; // [esp+28h] [ebp-Ch] BYREF

  rf_vector3_default_construct_noop(v5);
  rf_matrix3_construct((char *)v4);
  rf_respawn_select_reordered_arguments(a1, v5, v4);
  v3 = (float *)rf_multiplayer_player_entity_create(a1, *(_DWORD *)(a1 + 24), (int)v5, (int)v4, *(_DWORD *)(a1 + 3932));
  rf_object_set_room_and_cache_position(v3, 0);
  rf_object_refresh_room_cache_and_audio(v3);
  first_dword = rf_receiver_get_first_dword(v3);
  rf_object_set_room_and_cache_position(**(float ***)(a1 + 196), first_dword);
  *(float *)(a1 + 4576) = 0.0;
  *(float *)(a1 + 4580) = 0.0;
  *(float *)(a1 + 4584) = 0.0;
  *(float *)(a1 + 4588) = 0.0;
  *(float *)(a1 + 4596) = 0.0;
  *(_BYTE *)(a1 + 4593) = 1;
  *(_BYTE *)(a1 + 4592) = 0;
  *(_BYTE *)(a1 + 4156) = 0;
  return v3;
}

