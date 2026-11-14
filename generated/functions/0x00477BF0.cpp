// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00477BF0 rf_world_bind_all_face_and_lightmap_textures
// UNREALRED VERIFIED [level-lifecycle-20261028]: Traverses world-solid face-list at solid+112 via next+84. For face bitmap handle+48>=0 invokes0x571C60. If signed s16 lightmap index+54>=0, obtains lightmap from solid+192 array and nested handle at *(record+12)+16; nonnegative handle is also bound. Then invokes0x525A70 to bind additional registered handles. No world-null or lightmap-index upper check. Mutates backend binding state; does not itself release texture handles.
int rf_world_bind_all_face_and_lightmap_textures()
{
  int v1; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = rf_receiver_get_first_dword((void *)(rf_world_solid + 112)); i; i = rf_solid_face_next_link(i) )
  {
    if ( *(int *)(i + 48) > -1 )
      rf_renderer_bind_texture_for_level_warmup(*(_DWORD *)(i + 48));
    if ( *(__int16 *)(i + 54) > -1 )
    {
      v1 = *(_DWORD *)(*(_DWORD *)sub_552200((_DWORD *)(rf_world_solid + 192), *(__int16 *)(i + 54)) + 12);
      if ( *(int *)(v1 + 16) > -1 )
        rf_renderer_bind_texture_for_level_warmup(*(_DWORD *)(v1 + 16));
    }
  }
  return rf_world_bind_registered_extra_textures();
}

