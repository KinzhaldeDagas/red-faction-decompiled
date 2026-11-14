// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B1E30 rf_scene_definition_get_or_load_cached_vsfx
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, VSFX header/version gates, pool ownership/cursors, FourCC dispatch, normal error cleanup and model postprocessing): Cdecl filename and context. Scans global scene pointer array1D6CF28 up to count1D6D24C, compares object-leading stored filename with stricmp and returns first matching scene. Context not part of cache key; no slash/path normalization or refcount increment. Miss calls reserved renderer no-op5709C0, allocates308 bytes, constructs empty pools5CA030 if allocation nonnull, then calls5CAF80 even if receiverNULL. False loader result unbounded-sprintf diagnostic into256-byte local and fatal anim_mesh.cpp266; no scene deletion/rollback before fatal. Successful result appended at cache[count++] WITHOUT capacity check, then reserved no-op5709D0. Returns shared scene pointer; no lock, eviction or input NULL guard.
char *__cdecl rf_scene_definition_get_or_load_cached_vsfx(char *String2, int a2)
{
  char *v3; // [esp+8h] [ebp-130h]
  _DWORD *v4; // [esp+14h] [ebp-124h]
  char Buffer[256]; // [esp+1Ch] [ebp-11Ch] BYREF
  char *v7; // [esp+124h] [ebp-14h]
  int i; // [esp+128h] [ebp-10h]
  int v9; // [esp+134h] [ebp-4h]

  v7 = nullptr;
  for ( i = 0; i < dword_1D6D24C; ++i )
  {
    if ( !_stricmp((&unk_1D6CF28)[i], String2) )
    {
      v7 = (&unk_1D6CF28)[i];
      break;
    }
  }
  if ( !v7 )
  {
    rf_renderer_reserved_noop_5709C0();
    v4 = operator new(0x134u);
    v9 = 0;
    if ( v4 )
      v3 = (char *)rf_scene_definition_construct_empty_pools(v4);
    else
      v3 = nullptr;
    v9 = -1;
    v7 = v3;
    if ( !rf_scene_definition_read_vsfx_binary(v3, String2, a2) )
    {
      sprintf(Buffer, "Unable to load animated effect %s.  File doesn't exist or is corrupt.", String2);
      rf_fatal_error_show_message_and_exit("D:\\projects\\rf_pc\\vsdk\\geom\\anim_mesh.cpp", 266, Buffer);
    }
    (&unk_1D6CF28)[dword_1D6D24C++] = v7;
    rf_renderer_reserved_noop_5709D0();
  }
  return v7;
}

