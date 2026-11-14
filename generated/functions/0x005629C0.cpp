// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005629C0 rf_model_handle_prepare_material_resources
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, tagged model bounds, scene transform propagation, by-value matrix ABI, named spheres and cyclic/action dispatch): Tag2 calls reserved character no-op587A50;tag1 calls generic helper unknown_libname_47;tag3 warms material textures on scene definition8. Other tags do nothing. No handle mutation, status return, or common resource-loading loop in this dispatcher itself.
void __thiscall rf_model_handle_prepare_material_resources(_DWORD *this)
{
  switch ( *this )
  {
    case 2:
      rf_character_reserved_noop_587A50();
      break;
    case 1:
      rf_model_resource_cleanup_noop_5b9830();
      break;
    case 3:
      rf_scene_definition_warm_material_textures((_DWORD *)*(this + 2));
      break;
  }
}

