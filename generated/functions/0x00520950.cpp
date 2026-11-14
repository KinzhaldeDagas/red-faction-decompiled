// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00520950 rf_world_collect_visible_rooms_and_sky
// [UnrealRed combat room owner 2026-11-12; verified original-byte ASM] Perpass start resets visible-list/count, room353/depth through520F70 and portal36/37 through520FE0; DOES NOT clear room352. Uses CURRENT renderer camera581FA0. Portal traversal depends on flag663AFC,ordinary156count>1 and nonnullstartroom; otherwise visits allordinary156 withflag1(no traversal). Complete352 producer must account for these per-view branches and prior render-group union.
int __cdecl rf_world_collect_visible_rooms_and_sky(int a1, int a2, int a3)
{
  int result; // eax
  int *v4; // eax
  bool v5; // [esp+7h] [ebp-39h]
  float v6[3]; // [esp+8h] [ebp-38h] BYREF
  int first_dword; // [esp+14h] [ebp-2Ch]
  float v8[9]; // [esp+18h] [ebp-28h] BYREF
  int i; // [esp+3Ch] [ebp-4h]

  rf_vector3_default_construct_noop(v6);
  rf_matrix3_construct((char *)v8);
  rf_renderer_copy_current_view_transform(v6, v8);
  first_dword = rf_receiver_get_first_dword((void *)(a1 + 156));
  v5 = 1;
  if ( dword_663AFC && first_dword > 1 )
    v5 = a2 == 0;
  dword_A42074 = 0;
  dword_A42078 = 0;
  unk_A4207C = 0;
  *(_DWORD *)&byte_98967F[756173] = first_dword;
  dword_A42078 = (int)rf_world_find_first_authored_sky_room(a1);
  rf_world_reset_room_visibility_state(a1);
  rf_world_reset_portal_visibility_state(a1);
  result = v5;
  if ( !v5 )
    return rf_world_visit_room_through_portal_apertures(a1, a2, nullptr, 0, a3, (int)v6);
  for ( i = 0; i < first_dword; ++i )
  {
    v4 = (int *)sub_552200((_DWORD *)(a1 + 156), i);
    result = rf_world_visit_room_through_portal_apertures(a1, *v4, nullptr, 0, a3 | 1, (int)v6);
  }
  return result;
}

