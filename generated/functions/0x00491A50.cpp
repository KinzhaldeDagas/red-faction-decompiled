// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00491A50 rf_respawn_point_select
// UNREALRED VERIFIED [respawn-decode]: Filters team flags at record +60/+61, writes score at +64, sorts ascending, and selects round((N-1)*sqrt(U)) from 68-byte records.
int __cdecl rf_respawn_point_select(float *destination, float *a2, int a3)
{
  float v4; // [esp+4h] [ebp-6Ch]
  float v5[3]; // [esp+10h] [ebp-60h] BYREF
  float v6[3]; // [esp+1Ch] [ebp-54h] BYREF
  void *v7; // [esp+28h] [ebp-48h]
  float v8[3]; // [esp+2Ch] [ebp-44h] BYREF
  float copy_result[3]; // [esp+38h] [ebp-38h] BYREF
  int v10; // [esp+44h] [ebp-2Ch]
  int v11; // [esp+48h] [ebp-28h]
  char *v12; // [esp+4Ch] [ebp-24h]
  int v13; // [esp+50h] [ebp-20h]
  int v14; // [esp+54h] [ebp-1Ch]
  int v15; // [esp+58h] [ebp-18h]
  float v16; // [esp+5Ch] [ebp-14h]
  signed int v17; // [esp+60h] [ebp-10h]
  void *Base; // [esp+64h] [ebp-Ch]
  size_t NumOfElements; // [esp+68h] [ebp-8h]
  int i; // [esp+6Ch] [ebp-4h]

  if ( rf_respawn_point_count <= 0 )
  {
    rf_vector3_zero_return_destination(destination);
    rf_identity_orientation_matrix(a2);
    return -1;
  }
  if ( !a3 )
  {
    v13 = rand() % rf_respawn_point_count;
    rf_vector_copy(destination, copy_result, (const float *)&unk_757BD4 + 17 * v13);
    rf_matrix3_copy(a2, (const float *)&unk_757BE0 + 17 * v13);
    return 0;
  }
  v17 = 0;
  v14 = rf_multiplayer_game_mode_get();
  for ( i = 0; i < rf_respawn_point_count; ++i )
  {
    v12 = &rf_respawn_points[68 * i];
    if ( v14 == 1 )
    {
      if ( *(_BYTE *)(a3 + 48) )
      {
        if ( *(_BYTE *)(a3 + 48) == 1 && !v12[61] )
        {
          *((float *)v12 + 16) = -1.0;
          continue;
        }
      }
      else if ( !v12[60] )
      {
        *((float *)v12 + 16) = -1.0;
        continue;
      }
    }
    *((float *)v12 + 16) = rf_respawn_point_safety_score((_DWORD *)a3, (float *)v12 + 3, nullptr);
    ++v17;
  }
  if ( v17 )
  {
    v7 = operator new(4 * v17);
    Base = v7;
    NumOfElements = 0;
    for ( i = 0; i < rf_respawn_point_count; ++i )
    {
      if ( unk_757C08[17 * i] > 0.0 && (int)NumOfElements < v17 )
        *((_DWORD *)Base + NumOfElements++) = &rf_respawn_points[68 * i];
    }
    if ( NumOfElements )
    {
      qsort(Base, NumOfElements, 4u, rf_respawn_score_pointer_compare);
      v4 = rf_random_float_range(0.0, 1.0);
      v16 = rf_sqrt_float(v4);
      v15 = (int)((double)(int)(NumOfElements - 1) * v16 + 0.5);
      rf_vector_copy(destination, v5, (const float *)(*((_DWORD *)Base + v15) + 12));
      rf_matrix3_copy(a2, (const float *)(*((_DWORD *)Base + v15) + 24));
      operator delete(Base);
    }
    else
    {
      v10 = rand() % rf_respawn_point_count;
      rf_vector_copy(destination, v6, (const float *)&unk_757BD4 + 17 * v10);
      rf_matrix3_copy(a2, (const float *)&unk_757BE0 + 17 * v10);
    }
    return 1;
  }
  else
  {
    v11 = rand() % rf_respawn_point_count;
    rf_vector_copy(destination, v8, (const float *)&unk_757BD4 + 17 * v11);
    rf_matrix3_copy(a2, (const float *)&unk_757BE0 + 17 * v11);
    return 1;
  }
}

