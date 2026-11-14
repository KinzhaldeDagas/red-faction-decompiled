// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00524D50 rf_world_decal_draw_first_polygon_on_face
// UNREALRED VERIFIED [decal-updates-20261028]: Finds first polygon in decal list+212 whose owner+1312 matches caller face. Copies vertex-count+208 world positions at polygon+228+44*i and base UV at+212/+216+44*i into static arrays of25 entries; no count<=25 guard. Lazily calls no-op vector constructors on static arrays. Sets state selector12, packs render state(1,1,3,3,1,0), uses white RGB and decal alpha byte+76, submits bitmap+60/vertex array/UV through0x580490, resets state selector0. No matching polygon returns incidental pointer; no draw count contract.
_DWORD *__cdecl rf_world_decal_draw_first_polygon_on_face(_DWORD *a1, int a2)
{
  _DWORD *result; // eax
  _DWORD *v3; // [esp+4h] [ebp-30h]
  float copy_result[3]; // [esp+8h] [ebp-2Ch] BYREF
  int v5; // [esp+14h] [ebp-20h] BYREF
  char v6[4]; // [esp+18h] [ebp-1Ch] BYREF
  _DWORD *v7; // [esp+1Ch] [ebp-18h]
  _DWORD *i; // [esp+20h] [ebp-14h]
  int j; // [esp+24h] [ebp-10h]
  int v10; // [esp+30h] [ebp-4h]

  v7 = nullptr;
  result = (_DWORD *)a2;
  for ( i = *(_DWORD **)(a2 + 212); i; i = v3 )
  {
    result = (_DWORD *)i[328];
    if ( result == a1 )
    {
      v7 = i;
      break;
    }
    result = (_DWORD *)a2;
    if ( i[330] == *(_DWORD *)(a2 + 212) )
    {
      v3 = nullptr;
    }
    else
    {
      result = (_DWORD *)i[330];
      v3 = result;
    }
  }
  if ( v7 )
  {
    if ( (dword_D024AC & 1) == 0 )
    {
      dword_D024AC |= 1u;
      rf_vector_construct_no_unwind((char *)unk_D02380, 0xCu, 25, rf_vector3_default_construct_noop);
      v10 = -1;
    }
    if ( (dword_D024AC & 2) == 0 )
    {
      dword_D024AC |= 2u;
      rf_vector_construct_no_unwind((char *)unk_D022B8, 8u, 25, rf_vector3_default_construct_noop);
      v10 = -1;
    }
    for ( j = 0; j < v7[52]; ++j )
    {
      rf_vector_copy(&unk_D02380[3 * j], copy_result, (const float *)&v7[11 * j + 57]);
      unk_D022B8[2 * j] = *(float *)&v7[11 * j + 53];
      unk_D022BC[2 * j] = *(float *)&v7[11 * j + 54];
    }
    rf_renderer_set_auxiliary_mode_clamped_0_16(12);
    rf_render_state_pack(&v5, 1, 1, 3, 3, 1, 0);
    v6[0] = -1;
    v6[1] = -1;
    v6[2] = -1;
    v6[3] = *(_BYTE *)(a2 + 76);
    rf_renderer_submit_textured_world_polygon_color4_dispatch(
      *(_DWORD *)(a2 + 60),
      v7[52],
      (int)unk_D02380,
      (int)unk_D022B8,
      v5,
      v6);
    return rf_renderer_set_auxiliary_mode_clamped_0_16(0);
  }
  return result;
}

