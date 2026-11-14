// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00420790 rf_entity_emit_death_explosion_debris
// UNREALRED VERIFIED [indirect-source-20261029] Entity death-explosion/debris path calls448DC0 with authored transformed offset/radius and scalar1.0. The shared helper supplies anonymous radial source -1; Entity+0x144C death-source metadata is not forwarded into this radial damage.
int __cdecl rf_entity_emit_death_explosion_debris(int a1)
{
  float *v1; // eax
  int first_dword; // eax
  int result; // eax
  char *v4; // eax
  float v5; // [esp+0h] [ebp-24h]
  float v6; // [esp+4h] [ebp-20h]
  float v7[3]; // [esp+Ch] [ebp-18h] BYREF
  int v8[3]; // [esp+18h] [ebp-Ch] BYREF

  rf_vector3_copy_return_destination((float *)v8, (float *)(a1 + 60));
  v1 = rf_vector3_transform_by_matrix_rows((float *)(*(_DWORD *)(a1 + 660) + 1792), v7, (float *)(a1 + 72));
  rf_vector_accumulate((float *)v8, v1);
  v5 = *(float *)(*(_DWORD *)(a1 + 660) + 1788);
  first_dword = rf_receiver_get_first_dword((void *)a1);
  sub_448DC0(*(_DWORD *)(*(_DWORD *)(a1 + 660) + 1784), first_dword, 0, (float *)v8, v5, 1.0, 0);
  result = rf_rf_string_not_equals_cstring_case_insensitive(*(_DWORD *)(a1 + 660) + 16, (char *)&byte_631A3F);
  if ( (_BYTE)result )
  {
    v6 = flt_6612F4;
    v4 = (char *)rf_string_object_c_str_or_empty((const void *)(*(_DWORD *)(a1 + 660) + 16));
    return (int)rf_clutter_spawn_authored_debris(a1, v4, -1, 10000, v6, nullptr);
  }
  return result;
}

