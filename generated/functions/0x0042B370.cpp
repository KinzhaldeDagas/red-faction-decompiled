// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042B370 rf_entity_update_runtime_vfx
// UNREALRED VERIFIED [weapon-shell-ejection-20261008] Entity+0x1374 shell deadline is tested, reset before 0x438170, and emits an additional casing if Entity+0x814 bit 0x1000 is set. This single timer coalesces/replaces pending primary ejection requests. The bit interpretation and cross-weapon lifetime remain separate boundaries; Unreal currently cancels stale weapon/source/death events.
void __cdecl rf_entity_update_runtime_vfx(_DWORD *a1)
{
  int v1[3]; // [esp+14h] [ebp-Ch] BYREF

  if ( a1[530] )
    rf_vfx_update_instance((int *)a1[530], rf_frame_delta_seconds, 0, 0, 0, 1);
  if ( rf_replicator_has_elapsed(a1 + 1245) )
  {
    rf_replicator_reset(a1 + 1245);
    rf_weapon_present_shell_ejection(a1);
    if ( (a1[517] & 0x1000) != 0 )
      rf_weapon_present_shell_ejection(a1);
  }
  if ( rf_entity_class_flag2000000_positive_scalar56((int)a1) )
  {
    rf_vector3_default_construct_noop(v1);
    rf_object_copy_node_or_common_world_position((int)a1, (int)v1);
    rf_vfx_update_instance(*(int **)(a1[532] + 4), rf_frame_delta_seconds, 0, (int)v1, (int)(a1 + 18), 1);
  }
  if ( a1[1315] )
  {
    rf_vfx_update_instance((int *)a1[1315], rf_frame_delta_seconds, 0, (int)(a1 + 15), (int)(a1 + 18), 1);
    if ( rf_vfx_get_remaining_time((const void *)a1[1315], 0) <= 0.0 )
    {
      rf_model_handle_destroy_cdecl_adapter((_DWORD *)a1[1315]);
      a1[1315] = 0;
    }
  }
}

