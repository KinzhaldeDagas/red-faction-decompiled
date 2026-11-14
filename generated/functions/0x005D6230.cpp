// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D6230 rf_renderer_draw_solid_faces_lit_with_alpha
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, immediate vertex conversion, face-list lighting, bump-stage calls and original PE bytes): Recovered cdecl(solid,four unusedDWORDs,optional origin,optional orientation,alpha byte),ending5D6565. Tests texture support against GLOBAL descriptor182ABB0,not its later local state. If both transform pointers nonNULL,pushes receiver transform through581260;syncs light receiver space. Local word constructed-1 then overwritten with packed(texture1,RGB4,alpha3 when alpha<255 else0,blend3,depth4,fog0). Sets current RGBA white/alpha. Face head is firstDWORD at solid+112,advanced through rf_solid_face_next_link. For every face initializes48 local RF48 vertices and48 pointer slots,sets pending texture(face+48,-1),walks circular face-vertex links from face+64(next+20,stops when next returns head). Transforms each referenced point,SUMS
// linked normal vectors from point+32 container then normalizes sum,computes nonworld diffuse RGB with supplied normal. Unsupported GLOBAL texture descriptor doubles each RGB BYTE with wraparound,not saturation. UV from face-link+4/+8;submits immediate polygon flags5 and local state (per-vertex RGB,current alpha,not vertex alpha). Restores transform through581290 only when both input pointers were nonNULL. Four unused arguments ignored. No48-vertex,face/normal list,pointer or polygon count guards. Alpha255 selects diffuse alpha and bypasses texture alpha;lower values select texture*diffuse alpha. Leaves pending texture/current color/state changed;EAX loop/pop result incidental,not success.
int __cdecl rf_renderer_draw_solid_faces_lit_with_alpha(
        void *a1,
        int a2,
        int a3,
        int a4,
        int a5,
        const float *a6,
        const float *a7,
        unsigned __int8 a8)
{
  int result; // eax
  int v9; // [esp+Ch] [ebp-A00h]
  int v10; // [esp+10h] [ebp-9FCh] BYREF
  int v11; // [esp+14h] [ebp-9F8h] BYREF
  float *v12; // [esp+18h] [ebp-9F4h]
  float v13[3]; // [esp+1Ch] [ebp-9F0h] BYREF
  int first_dword; // [esp+28h] [ebp-9E4h]
  char *v15; // [esp+2Ch] [ebp-9E0h]
  int k; // [esp+30h] [ebp-9DCh]
  int j; // [esp+34h] [ebp-9D8h]
  int v18; // [esp+38h] [ebp-9D4h]
  _DWORD v19[48]; // [esp+3Ch] [ebp-9D0h] BYREF
  char v20[2308]; // [esp+FCh] [ebp-910h] BYREF
  unsigned int v21; // [esp+A00h] [ebp-Ch] BYREF
  bool v22; // [esp+A07h] [ebp-5h]
  int i; // [esp+A08h] [ebp-4h]

  v22 = rf_renderer_texture_mode_supported_dispatch((int)&unk_182ABB0) == 0;
  if ( a6 && a7 )
    rf_renderer_push_instance_transform_dispatch((int)a6, (int)a7);
  rf_light_sync_active_receiver_space_if_enabled();
  rf_dword_construct_invalid_minus_one(&v21);
  if ( a8 == 255 )
    v21 = *rf_render_state_pack(&v10, 1, 4, 0, 3, 4, 0);
  else
    v21 = *rf_render_state_pack(&v11, 1, 4, 3, 3, 4, 0);
  rf_render_color_set_rgba8(255, 255, 255, a8);
  result = rf_receiver_get_first_dword((char *)a1 + 112);
  for ( i = result; i; i = result )
  {
    rf_vector_construct_no_unwind(v20, 0x30u, 48, rf_vector_prefix_construct_noop);
    v18 = 0;
    rf_renderer_set_pending_texture_handles(*(_DWORD *)(i + 48), -1);
    for ( j = *(_DWORD *)(i + 64); j; j = v9 )
    {
      v15 = &v20[48 * v18];
      v19[v18++] = v15;
      rf_renderer_transform_world_point_backend_wrapper((int)v15, *(float **)j);
      rf_vector3_set_components_return_destination(v13, 0.0, 0.0, 0.0);
      first_dword = rf_receiver_get_first_dword((void *)(*(_DWORD *)j + 32));
      for ( k = 0; k < first_dword; ++k )
      {
        v12 = *(float **)sub_552200((_DWORD *)(*(_DWORD *)j + 32), k);
        rf_vector_accumulate(v13, v12);
      }
      rf_vector_normalize(v13);
      rf_renderer_compute_nonworld_diffuse_rgb8(v15 + 44, v15 + 45, v15 + 46, 1, *(float **)j, v13, -1.0);
      if ( v22 )
      {
        v15[44] *= 2;
        v15[45] *= 2;
        v15[46] *= 2;
      }
      *((float *)v15 + 7) = *(float *)(j + 4);
      *((float *)v15 + 8) = *(float *)(j + 8);
      if ( *(_DWORD *)(j + 20) == *(_DWORD *)(i + 64) )
        v9 = 0;
      else
        v9 = *(_DWORD *)(j + 20);
    }
    rf_renderer_submit_immediate_polygon(v18, (int)v19, 5, v21, 0, 0.0);
    result = rf_solid_face_next_link(i);
  }
  if ( a6 && a7 )
    return rf_renderer_pop_instance_transform_dispatch();
  return result;
}

