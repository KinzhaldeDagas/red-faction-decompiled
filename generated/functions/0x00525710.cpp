// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00525710 rf_world_decal_update_lightmap_uvs
// UNREALRED VERIFIED [decal-updates-20261028]: Traverses active decals; skips flags+80 mask8. For each polygon, reads signed owner-face lightmap index at *(polygon+1312)+54. Nonnegative index selects lightmap in decal context+232 array at+192; stores nested texture handle *(lightmap+12)+16 at polygon+204. For each vertex(count+208), extracts world-position components from polygon+228+44*i using axis indices lightmap+96/+100, scales by lightmap+76/+80, adds vec2 offset+84, stores UV at polygon+220/+224+44*i and clamps each0..1. No context/owner/lightmap upper bounds guard; negative lightmap index leaves previous fields unchanged.
_DWORD *rf_world_decal_update_lightmap_uvs()
{
  _DWORD *result; // eax
  float *v1; // eax
  float v2; // [esp+4h] [ebp-28h]
  int v3; // [esp+8h] [ebp-24h]
  _DWORD *v4; // [esp+Ch] [ebp-20h]
  float v5; // [esp+10h] [ebp-1Ch] BYREF
  float v6; // [esp+14h] [ebp-18h]
  int v7; // [esp+18h] [ebp-14h]
  int v8; // [esp+1Ch] [ebp-10h]
  int k; // [esp+20h] [ebp-Ch]
  _DWORD *j; // [esp+24h] [ebp-8h]
  _DWORD *i; // [esp+28h] [ebp-4h]

  result = (_DWORD *)unk_A7051C;
  for ( i = (_DWORD *)unk_A7051C; i; i = (_DWORD *)v3 )
  {
    if ( (i[20] & 8) == 0 )
    {
      for ( j = (_DWORD *)i[53]; j; j = v4 )
      {
        if ( *(__int16 *)(j[328] + 54) >= 0 )
        {
          v7 = *(_DWORD *)sub_552200((_DWORD *)(i[58] + 192), *(__int16 *)(j[328] + 54));
          v8 = *(_DWORD *)(v7 + 12);
          j[51] = *(_DWORD *)(v8 + 16);
          for ( k = 0; k < j[52]; ++k )
          {
            v2 = *(float *)rf_vector_component_address_unchecked((char *)&j[11 * k + 57], *(_DWORD *)(v7 + 100));
            v1 = (float *)rf_vector_component_address_unchecked((char *)&j[11 * k + 57], *(_DWORD *)(v7 + 96));
            rf_vector2_assign_components(&v5, *v1, v2);
            v5 = v5 * *(float *)(v7 + 76);
            v6 = v6 * *(float *)(v7 + 80);
            rf_vector2_accumulate(&v5, (float *)(v7 + 84));
            *(float *)&j[11 * k + 55] = v5;
            *(float *)&j[11 * k + 56] = v6;
            rf_float_clamp_in_place((float *)&j[11 * k + 55], 0.0, 1.0);
            rf_float_clamp_in_place((float *)&j[11 * k + 56], 0.0, 1.0);
          }
        }
        if ( j[330] == i[53] )
          v4 = nullptr;
        else
          v4 = (_DWORD *)j[330];
      }
    }
    result = i;
    if ( i[56] == unk_A7051C )
    {
      v3 = 0;
    }
    else
    {
      result = (_DWORD *)i[56];
      v3 = (int)result;
    }
  }
  return result;
}

