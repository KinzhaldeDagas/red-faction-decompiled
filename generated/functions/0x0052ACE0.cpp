// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052ACE0 sub_52ACE0
// UNREALRED VERIFIED [combat-native-query-20261104]: Postpair corner-limit cleanup applies534F50 to faces with more than16 ordered corners; caller52BE50 runs it over active and backup lists irrespective of operand. Mode6 cannot assume only the liquid cutter changes ownership/order.
_DWORD *__cdecl sub_52ACE0(int a1, void *a2)
{
  _DWORD *result; // eax
  int v3; // [esp+0h] [ebp-18h] BYREF
  int v4; // [esp+4h] [ebp-14h] BYREF
  _DWORD *link; // [esp+8h] [ebp-10h]
  _DWORD *v6; // [esp+Ch] [ebp-Ch]
  int v7; // [esp+10h] [ebp-8h]
  _DWORD *i; // [esp+14h] [ebp-4h]

  result = (_DWORD *)rf_receiver_get_first_dword(a2);
  for ( i = result; i; i = link )
  {
    v6 = i;
    link = (_DWORD *)rf_solid_face_next_link((int)i);
    v7 = rf_geomod_face_corner_count(v6);
    if ( v7 <= 16 )
    {
      result = (_DWORD *)(i[10] & 0x200000);
      if ( result )
      {
        if ( (i[10] & 0x80000) != 0 )
        {
          i[10] &= ~0x80000u;
          result = (_DWORD *)rf_face_update_flag8_decal_base_uvs(a1, (int)i);
        }
      }
    }
    else
    {
      rf_geomod_face_split_for_corner_limit(a1, (int)i, &v3, &v4);
      rf_solid_face_list_remove((int *)a2, (int)i);
      result = (_DWORD *)rf_geomod_face_destroy(i);
    }
  }
  return result;
}

