// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005CE260 rf_scene_definition_warm_material_textures
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, scene instance dispatch, allocation/deletion callers, pool strides and key constructors): Walks materialCount+136,200-byte materials at pointer+140;for each2 texture slots,stride52,handle at+16,binds nonnegative handle via rf_renderer_bind_texture_for_level_warmup. No handle load,generation or balanced renderer-state restoration. Ignores negative handles,not material-type-specific; EAX incidental loop result.
int __thiscall rf_scene_definition_warm_material_textures(_DWORD *this)
{
  int result; // eax
  int j; // [esp+4h] [ebp-8h]
  int i; // [esp+8h] [ebp-4h]

  for ( i = 0; i < *(this + 34); ++i )
  {
    for ( j = 0; j < 2; ++j )
    {
      if ( *(int *)(*(this + 35) + 200 * i + 52 * j + 16) >= 0 )
        rf_renderer_bind_texture_for_level_warmup(*(_DWORD *)(200 * i + *(this + 35) + 52 * j + 16));
    }
    result = i + 1;
  }
  return result;
}

