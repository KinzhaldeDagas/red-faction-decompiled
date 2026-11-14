// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005D75A0 rf_renderer_submit_room_faces
// UNREALRED VERIFIED [sky-face-render-contract] Submits a room's face list only after rejecting invisible bit 0x2000, ShowSky bit 0x01, and a positive signed portal marker (subject to the two explicit debug overrides). Accepted bit-0x40 faces enter the see-through queue; the remainder enter the opaque queue.
void __cdecl rf_renderer_submit_room_faces(int a1, float *a2, char *a3)
{
  float v3[3]; // [esp+0h] [ebp-20090h] BYREF
  float v4[3]; // [esp+Ch] [ebp-20084h] BYREF
  float v5[3]; // [esp+18h] [ebp-20078h] BYREF
  float v6[3]; // [esp+24h] [ebp-2006Ch] BYREF
  float v7[3]; // [esp+30h] [ebp-20060h] BYREF
  float copy_result[3]; // [esp+3Ch] [ebp-20054h] BYREF
  float source[3]; // [esp+48h] [ebp-20048h] BYREF
  float v10[3]; // [esp+54h] [ebp-2003Ch] BYREF
  float destination[3]; // [esp+60h] [ebp-20030h] BYREF
  float v12[3]; // [esp+6Ch] [ebp-20024h] BYREF
  _DWORD v13[16385]; // [esp+78h] [ebp-20018h] BYREF
  float *i; // [esp+1007Ch] [ebp-10014h]
  _DWORD v15[16385]; // [esp+10080h] [ebp-10010h] BYREF
  char active_list_context_byte; // [esp+20087h] [ebp-9h]
  int v17; // [esp+20088h] [ebp-8h]
  int v18; // [esp+2008Ch] [ebp-4h]

  v18 = 0;
  v17 = 0;
  ++*(_DWORD *)(a1 + 860);
  if ( a2 && a3 )
    rf_renderer_push_instance_transform_dispatch((int)a2, (int)a3);
  for ( i = (float *)rf_receiver_get_first_dword((void *)(a1 + 112)); i; i = (float *)rf_solid_face_next_link((int)i) )
  {
    if ( (!rf_face_is_invisible((_DWORD *)i + 10) || unk_A420A8)
      && ((_DWORD)i[10] & 1) == 0
      && (!rf_face_is_portal((__int16 *)i + 20) || unk_A42094)
      && rf_renderer_face_passes_view_test(i) )
    {
      if ( rf_face_is_see_through((_DWORD *)i + 10) )
        v13[v18++] = i;
      else
        v15[v17++] = i;
      if ( ((_DWORD)i[10] & 0x400) != 0 )
        rf_procedural_bitmap_mark_used_by_handle(*((_DWORD *)i + 12));
    }
  }
  *(_DWORD *)&byte_98967F[756185] += v18 + v17;
  active_list_context_byte = rf_light_get_active_list_context_byte();
  if ( !active_list_context_byte )
  {
    rf_vector3_default_construct_noop(source);
    rf_vector3_default_construct_noop(v10);
    rf_vector3_default_construct_noop(destination);
    rf_vector3_default_construct_noop(v12);
    rf_aabb_transform_matrix_translate(a3, a2, (char *)(a1 + 72), (char *)(a1 + 84), source, v10);
    rf_vector_copy(destination, copy_result, (const float *)(a1 + 72));
    rf_vector_copy(v12, v7, (const float *)(a1 + 84));
    rf_vector_copy((float *)(a1 + 72), v6, source);
    rf_vector_copy((float *)(a1 + 84), v5, v10);
    rf_light_build_active_list_for_world_receiver(a1, 1, 0);
    rf_vector_copy((float *)(a1 + 72), v4, destination);
    rf_vector_copy((float *)(a1 + 84), v3, v12);
    rf_light_sync_active_receiver_space_if_enabled();
  }
  rf_procedural_bitmap_update_marked_records();
  rf_renderer_draw_face_batch_backend_102(a1, 0, v17, (int)v15, 0, 0);
  rf_renderer_draw_face_batch_backend_102(a1, 0, v18, (int)v13, 0, 1);
  if ( !active_list_context_byte )
    rf_light_clear_active_world_list();
  if ( a2 && a3 )
    rf_renderer_pop_instance_transform_dispatch();
}

