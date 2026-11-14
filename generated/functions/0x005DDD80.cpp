// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005DDD80 rf_renderer_draw_transformed_solid_faces
// UNREALRED VERIFIED [renderer-lighting-20261028]: Arguments solidcontext,worldtranslation,orientationmatrix,wireoverlaybyte. Lazily initializes unused-in-body packedstate(5,1,2,0,4,0),increments solidstamp+860. Walks solidface list+112; rejects flags+40 bit1,portals unless0xA42094,and failed rf_renderer_face_view_test_backend_102. Opaque faces processed immediately,see-throughfaces queued in local16384-pointerarray then processed in insertionorder WITHOUT depthsorting. Before each draw,if signedlightmapindex+54>=0 and lightmapbyte+8nonzero,saves recordAABB+52/+64,transforms bounds by suppliedmatrix/translation0x5B1A00,conditionallyupdates lightmap0x558330,then restoresoriginalbounds. Drawsface0x5DEEA0,passingwireoverlay. Accepted flag0x400 faces mark base proceduralbitmapused. Ends updating markedproceduralrecords and unbinding texturestages0/1. No translucentqueuecapacityguard or
// state/color restoration. Lightmapdirtyupdates not deduplicated here; repeatedface references may update same record according tocallee flags. Returns stage1unbindresult,not renderedcount.
int __cdecl rf_renderer_draw_transformed_solid_faces(_DWORD *a1, float *a2, char *a3, char a4)
{
  float v5[3]; // [esp+4h] [ebp-10088h] BYREF
  float v6[3]; // [esp+10h] [ebp-1007Ch] BYREF
  float v7[3]; // [esp+1Ch] [ebp-10070h] BYREF
  float copy_result[3]; // [esp+28h] [ebp-10064h] BYREF
  float v9[3]; // [esp+34h] [ebp-10058h] BYREF
  float v10[3]; // [esp+40h] [ebp-1004Ch] BYREF
  int v11; // [esp+4Ch] [ebp-10040h]
  float source[3]; // [esp+50h] [ebp-1003Ch] BYREF
  float v13[3]; // [esp+5Ch] [ebp-10030h] BYREF
  int v14; // [esp+68h] [ebp-10024h]
  int v15; // [esp+6Ch] [ebp-10020h]
  _DWORD v16[16385]; // [esp+70h] [ebp-1001Ch]
  float *i; // [esp+10074h] [ebp-18h]
  int j; // [esp+10078h] [ebp-14h]
  int v19; // [esp+1007Ch] [ebp-10h]
  int v20; // [esp+10088h] [ebp-4h]

  v19 = 0;
  v15 = 0;
  if ( (dword_1E01528 & 1) == 0 )
  {
    dword_1E01528 |= 1u;
    rf_render_state_pack(&dword_1E01524, 5, 1, 2, 0, 4, 0);
    v20 = -1;
  }
  ++a1[215];
  for ( i = (float *)rf_receiver_get_first_dword(a1 + 28); i; i = (float *)rf_solid_face_next_link((int)i) )
  {
    if ( ((_DWORD)i[10] & 1) == 0
      && (!rf_face_is_portal((__int16 *)i + 20) || unk_A42094)
      && rf_renderer_face_view_test_backend_102(i) )
    {
      if ( rf_face_is_see_through((_DWORD *)i + 10) )
      {
        v16[v19++] = i;
      }
      else
      {
        if ( *((__int16 *)i + 27) > -1 )
        {
          v14 = *(_DWORD *)sub_552200(a1 + 48, *((__int16 *)i + 27));
          if ( *(_BYTE *)(v14 + 8) )
          {
            ++v15;
            rf_vector3_copy_return_destination(source, (float *)(v14 + 52));
            rf_vector3_copy_return_destination(v13, (float *)(v14 + 64));
            rf_aabb_transform_matrix_translate(
              a3,
              a2,
              (char *)source,
              (char *)v13,
              (float *)(v14 + 52),
              (float *)(v14 + 64));
            rf_lightmap_update_record_timed_if_enabled((int)a1, v14);
            rf_vector_copy((float *)(v14 + 52), copy_result, source);
            rf_vector_copy((float *)(v14 + 64), v7, v13);
          }
        }
        rf_renderer_draw_cached_face_select_single_or_multipass((int)a1, (int)i, a4);
      }
      if ( ((_DWORD)i[10] & 0x400) != 0 )
        rf_procedural_bitmap_mark_used_by_handle(*((_DWORD *)i + 12));
    }
  }
  for ( j = 0; j < v19; ++j )
  {
    i = (float *)v16[j];
    if ( *((__int16 *)i + 27) > -1 )
    {
      v11 = *(_DWORD *)sub_552200(a1 + 48, *((__int16 *)i + 27));
      if ( *(_BYTE *)(v11 + 8) )
      {
        ++v15;
        rf_vector3_copy_return_destination(v9, (float *)(v11 + 52));
        rf_vector3_copy_return_destination(v10, (float *)(v11 + 64));
        rf_aabb_transform_matrix_translate(a3, a2, (char *)v9, (char *)v10, (float *)(v11 + 52), (float *)(v11 + 64));
        rf_lightmap_update_record_timed_if_enabled((int)a1, v11);
        rf_vector_copy((float *)(v11 + 52), v6, v9);
        rf_vector_copy((float *)(v11 + 64), v5, v10);
      }
    }
    rf_renderer_draw_cached_face_select_single_or_multipass((int)a1, (int)i, a4);
  }
  rf_procedural_bitmap_update_marked_records();
  rf_renderer_bind_texture_handle(0, -1, 0, 0, 0, 0);
  return rf_renderer_bind_texture_handle(1, -1, 0, 0, 0, 0);
}

