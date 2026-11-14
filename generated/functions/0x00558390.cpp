// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00558390 rf_solid_debug_draw_with_selection_overlays
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, solid clone side effects, UV frame mapping, debug geometry, vector aliasing and by-value ABI): ECX solid plus wireframe,faceAlphaByte,drawVertices,instanceTranslation,instanceOrientation,R,G,B; RET32. Compares renderer light-change serial to Solid884, stores new serial if changed, then iterates all vertices with EMPTY body. Resets render-pass state5582F0 and pushes instance transform. Wire mode draws all solid outlines in requested RGB then selected-face outlines red. Filled mode draws transformed solid faces with alpha, face-attached decals only for nonportal faces, then selected-face green overlays. Optional vertex marks are XYZ crosses half-length0.2, selected vertices red, others cyan. Pops instance BEFORE drawing global debug-line array D4C548(count/records), using packedRGB bytes0..2 and endpoints4/16. No
// color/state restoration beyond transform pop; return loop count incidental.
void __thiscall rf_solid_debug_draw_with_selection_overlays(
        void *this,
        unsigned __int8 a2,
        unsigned __int8 a3,
        unsigned __int8 a4,
        const float *a5,
        const float *a6,
        int a7,
        int a8,
        int a9)
{
  int *v9; // eax
  int *v10; // eax
  int first_dword; // eax
  int v12; // eax
  float v13; // [esp+28h] [ebp-50h]
  float v14; // [esp+2Ch] [ebp-4Ch]
  float v15; // [esp+30h] [ebp-48h]
  float v16; // [esp+34h] [ebp-44h]
  float v17; // [esp+38h] [ebp-40h]
  float v18; // [esp+3Ch] [ebp-3Ch]
  float *v20; // [esp+44h] [ebp-34h]
  float v21; // [esp+48h] [ebp-30h] BYREF
  float v22; // [esp+4Ch] [ebp-2Ch]
  float v23; // [esp+50h] [ebp-28h]
  int index; // [esp+54h] [ebp-24h]
  float v25; // [esp+58h] [ebp-20h]
  float *v26; // [esp+5Ch] [ebp-1Ch]
  int v27; // [esp+60h] [ebp-18h]
  int v28; // [esp+64h] [ebp-14h]
  int v29; // [esp+68h] [ebp-10h]
  int j; // [esp+6Ch] [ebp-Ch]
  unsigned int v31; // [esp+70h] [ebp-8h]
  int i; // [esp+74h] [ebp-4h]

  v31 = rf_renderer_get_light_change_serial();
  if ( *((_DWORD *)this + 221) != v31 )
  {
    *((_DWORD *)this + 221) = v31;
    for ( i = 0; i < rf_receiver_get_first_dword((char *)this + 120); ++i )
      ;
  }
  rf_render_pass_reset_counter_and_flags();
  rf_renderer_push_instance_transform_dispatch((int)a5, (int)a6);
  if ( a2 )
  {
    rf_render_color_set_rgba8(a7, a8, a9, 255);
    rf_renderer_solid_wire_outlines_backend_wrapper((int)this);
    rf_render_color_set_rgba8(255, 0, 0, 255);
    for ( i = 0; i < rf_receiver_get_first_dword((char *)this + 216); ++i )
    {
      v9 = (int *)sub_552200((_DWORD *)this + 54, i);
      rf_renderer_face_wire_outline_backend_wrapper((int)this, *v9);
    }
  }
  else
  {
    rf_render_color_set_rgba8(a7, a8, a9, 255);
    rf_renderer_transformed_solid_faces_backend_wrapper((int)this, (float *)a5, (int)a6, a3);
    for ( j = rf_receiver_get_first_dword((char *)this + 112); j; j = rf_solid_face_next_link(j) )
    {
      if ( !rf_face_is_portal((__int16 *)(j + 40)) )
        rf_world_decal_draw_records_attached_to_face(j);
    }
    for ( i = 0; i < rf_receiver_get_first_dword((char *)this + 216); ++i )
    {
      v10 = (int *)sub_552200((_DWORD *)this + 54, i);
      rf_renderer_face_green_overlay_backend_wrapper(*v10);
    }
  }
  if ( a4 )
  {
    for ( i = 0; ; ++i )
    {
      first_dword = rf_receiver_get_first_dword((char *)this + 120);
      if ( i >= first_dword )
        break;
      v26 = *(float **)sub_552200((_DWORD *)this + 30, i);
      rf_vector3_copy_return_destination(&v21, v26);
      index = rf_pointer_array_find_index((_DWORD *)this + 51, (int)v26);
      if ( index < 0 )
      {
        v27 = 0;
        v28 = 255;
        v29 = 255;
      }
      else
      {
        v27 = 255;
        v28 = 0;
        v29 = 0;
      }
      v25 = 0.2;
      v18 = v21 + (float)0.2;
      v17 = v21 - (float)0.2;
      rf_renderer_draw_rgb_world_line_components(v17, v22, v23, v18, v22, v23, v27, v28, v29, dword_182ABA0);
      v16 = v22 + v25;
      v15 = v22 - v25;
      rf_renderer_draw_rgb_world_line_components(v21, v15, v23, v21, v16, v23, v27, v28, v29, dword_182ABA0);
      v14 = v23 + v25;
      v13 = v23 - v25;
      rf_renderer_draw_rgb_world_line_components(v21, v22, v13, v21, v22, v14, v27, v28, v29, dword_182ABA0);
    }
  }
  rf_renderer_pop_instance_transform_dispatch();
  for ( i = 0; ; ++i )
  {
    v12 = rf_receiver_get_first_dword(dword_D4C548);
    if ( i >= v12 )
      break;
    v20 = *(float **)sub_552200(dword_D4C548, i);
    rf_renderer_draw_rgb_world_line_components(
      v20[1],
      v20[2],
      v20[3],
      v20[4],
      v20[5],
      v20[6],
      *(unsigned __int8 *)v20,
      *((unsigned __int8 *)v20 + 1),
      *((unsigned __int8 *)v20 + 2),
      dword_182ABA0);
  }
}

