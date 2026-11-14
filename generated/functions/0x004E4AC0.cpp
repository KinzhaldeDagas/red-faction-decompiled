// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004E4AC0 rf_player_apply_vehicle_camera_node_and_cache_transform
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, cockpit material/animation, vehicle camera nodes and integer gauge ABI): Cdecl(player,optional entity,in/out float3 position,in/out float9 matrix). NULL entity exits with outputs/player cache untouched. Player mode4292 selects1 view_left(global87C6AC),2 view_rear(87C6A8),3 view_right(87C6A4). For selected view, cached node<=0 triggers lookup against entity model128 (valid node0 is retried next call); even negative lookup result is forwarded to compose helper, no rejection. Compose using entity position60/matrix72 into supplied outputs. Mode0 or other values leaves supplied transform unchanged, but every nonNULL entity path copies it to player position4244/matrix4256. Global caches are not keyed by model/entity and not reset here. No output-pointer/playerNULL check.
void __cdecl rf_player_apply_vehicle_camera_node_and_cache_transform(int a1, int a2, float *source, float *a4)
{
  int v4; // [esp+0h] [ebp-10h]
  float copy_result[3]; // [esp+4h] [ebp-Ch] BYREF

  if ( a2 )
  {
    v4 = *(_DWORD *)(a1 + 4292);
    switch ( v4 )
    {
      case 1:
        if ( dword_87C6AC <= 0 )
          dword_87C6AC = rf_model_handle_find_node_adapter(*(_DWORD *)(a2 + 128), "view_left");
        rf_vmesh_compose_prop_world_transform(
          *(_DWORD *)(a2 + 128),
          dword_87C6AC,
          (float *)(a2 + 72),
          a2 + 60,
          (int)a4,
          source);
        break;
      case 2:
        if ( dword_87C6A8 <= 0 )
          dword_87C6A8 = rf_model_handle_find_node_adapter(*(_DWORD *)(a2 + 128), "view_rear");
        rf_vmesh_compose_prop_world_transform(
          *(_DWORD *)(a2 + 128),
          dword_87C6A8,
          (float *)(a2 + 72),
          a2 + 60,
          (int)a4,
          source);
        break;
      case 3:
        if ( dword_87C6A4 <= 0 )
          dword_87C6A4 = rf_model_handle_find_node_adapter(*(_DWORD *)(a2 + 128), "view_right");
        rf_vmesh_compose_prop_world_transform(
          *(_DWORD *)(a2 + 128),
          dword_87C6A4,
          (float *)(a2 + 72),
          a2 + 60,
          (int)a4,
          source);
        break;
    }
    rf_vector_copy((float *)(a1 + 4244), copy_result, source);
    rf_matrix3_copy((float *)(a1 + 4256), a4);
  }
}

