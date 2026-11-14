// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0052EC40 rf_geomod_boolean_mode6_face_policy_apply
// UNREALRED VERIFIED [geomod-lighting-20261027] The mode-6 commit first applies face action policy and attaches retained unowned faces, rebases primary per-corner UVs on cutter operands, then reverse-clones cutter faces through 0x534840 and attaches them to the affected room. Clone copies per-corner position/UV attributes before reversing loop + normal/plane. Source topology/UV identity must remain distinct from Unreal-specific raster front-face adaptation. The host persistent aperture transport is a modern enhancement; no native persistent fill-light claim is made here.
_DWORD *__cdecl rf_geomod_boolean_mode6_face_policy_apply(int a1, int a2, float *a3)
{
  _DWORD *v3; // esi
  _DWORD *result; // eax
  int v5; // [esp+4h] [ebp-1Ch]
  int v6; // [esp+8h] [ebp-18h]
  _DWORD *v7; // [esp+Ch] [ebp-14h]
  int v8; // [esp+10h] [ebp-10h]
  int v9; // [esp+14h] [ebp-Ch]
  int link; // [esp+18h] [ebp-8h]
  _DWORD *i; // [esp+1Ch] [ebp-4h]
  _DWORD *j; // [esp+1Ch] [ebp-4h]
  _DWORD *k; // [esp+1Ch] [ebp-4h]
  int m; // [esp+1Ch] [ebp-4h]

  for ( i = (_DWORD *)rf_receiver_get_first_dword((void *)(a1 + 112)); i; i = (_DWORD *)link )
  {
    link = rf_solid_face_next_link((int)i);
    v3 = &rf_geomod_boolean_action_table[40 * rf_geomod_face_operand_get(i + 10) + 5 * a2];
    v5 = v3[rf_geomod_face_boolean_class_get(i + 10)];
    if ( v5 == 1 )
    {
      rf_solid_face_list_remove((int *)(a1 + 112), (int)i);
      rf_geomod_face_destroy(i);
    }
    else if ( v5 == 2 && !i[17] )
    {
      rf_geomod_room_face_attach(a3, (int)i);
    }
  }
  for ( j = (_DWORD *)rf_receiver_get_first_dword((void *)(a1 + 112)); j; j = (_DWORD *)v9 )
  {
    v9 = rf_solid_face_next_link((int)j);
    if ( rf_geomod_face_operand_get(j + 10) )
      rf_geomod_face_primary_uv_rebase(j);
  }
  for ( k = (_DWORD *)rf_receiver_get_first_dword((void *)(a1 + 112)); k; k = (_DWORD *)v8 )
  {
    v8 = rf_solid_face_next_link((int)k);
    if ( rf_geomod_face_operand_get(k + 10) )
    {
      v7 = rf_geomod_face_clone_reversed(k, a1);
      rf_geomod_boolean_workspace_face_prepend((_DWORD *)(a1 + 112), (int)v7);
      rf_geomod_room_face_attach(a3, (int)v7);
    }
  }
  for ( m = rf_receiver_get_first_dword((void *)(a1 + 112)); m; m = v6 )
  {
    v6 = rf_solid_face_next_link(m);
    rf_solid_face_list_remove((int *)(a1 + 112), m);
    rf_solid_face_list_append(&dword_D4C528, m);
  }
  *(_DWORD *)(a1 + 112) = dword_D4C528;
  *(_DWORD *)(a1 + 116) = unk_D4C52C;
  result = rf_intrusive_list_reset_head_tail(&dword_D4C528);
  rf_geomod_primary_affected_room = a3;
  return result;
}

