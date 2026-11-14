// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC190 rf_event_teleport_apply
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type4 Teleport. Accept only common runtime types0,1,4. If associated entity at owner+0x200 resolves, call0x4343A0(association,target id,0). Copy event position+0x40 to owner predicted position+0xF0 and use0x4BC330 position/bounds setter; orientation-copy calls use event+0x4C. Entity-specific continuation updates view orientation/action profile, conditionally0x4D98A0, assigns AI mode2(-1,-1), then calls route/context helper0x40FD80 with event position and entity fields. Item/clutter paths do not run entity continuation. No damage, full velocity reset or successful-route requirement in entry gates.
int __cdecl rf_event_teleport_apply(const float *a1)
{
  int result; // eax
  int *v2; // eax
  float v3; // [esp+Ch] [ebp-38h]
  float copy_result[3]; // [esp+18h] [ebp-2Ch] BYREF
  float v5; // [esp+24h] [ebp-20h] BYREF
  float v6; // [esp+28h] [ebp-1Ch] BYREF
  float v7; // [esp+2Ch] [ebp-18h] BYREF
  char v8; // [esp+33h] [ebp-11h]
  int v9; // [esp+34h] [ebp-10h]
  int v10; // [esp+38h] [ebp-Ch]
  int v11; // [esp+3Ch] [ebp-8h]
  int i; // [esp+40h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 167));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)a1 + 167, i);
    v11 = rf_object_resolve_handle(*v2);
    if ( v11 && (*(_DWORD *)(v11 + 36) < 2u || *(_DWORD *)(v11 + 36) == 4) )
    {
      v10 = rf_entity_resolve_handle(*(_DWORD *)(v11 + 512));
      if ( v10 )
        rf_entity_detach_first_matching_child(v10, *(_DWORD *)(v11 + 44), 0);
      rf_vector_copy((float *)(v11 + 240), copy_result, a1 + 16);
      rf_object_publish_position_and_bounds(v11, (float *)a1 + 16);
      rf_matrix3_copy((float *)(v11 + 72), a1 + 19);
      rf_matrix3_copy((float *)(v11 + 252), a1 + 19);
      rf_matrix3_copy((float *)(v11 + 288), a1 + 19);
      v9 = rf_entity_resolve_handle(*(_DWORD *)(v11 + 44));
      if ( v9 )
      {
        rf_matrix3_copy((float *)(v9 + 2016), a1 + 19);
        rf_vector3_default_construct_noop(&v5);
        rf_matrix3_extract_euler_angles_retail((float *)(v9 + 72), &v5, &v7, &v6);
        v3 = -v5;
        rf_vector3_set_components_thiscall((float *)(v9 + 2148), v3, v6, v7);
        if ( rf_entity_admits_speech_body_actions(v9) )
          rf_model_handle_reset_actions_adapter(*(_DWORD *)(v9 + 128));
        if ( sub_438010(v9) )
          rf_object_snap_down_using_physics_shape_sweep(v9);
        v8 = *(_DWORD *)(*(_DWORD *)(v9 + 2136) + 4) == 1;
        rf_ai_numeric_mode_write((_DWORD *)(v9 + 672), 2, -1, -1);
        sub_40FD80(
          (float *)a1 + 16,
          *(float *)(v9 + 1984),
          *(float *)(v9 + 1988),
          v8,
          (int *)(v9 + 1692),
          (int *)(v9 + 1696),
          0);
      }
    }
  }
  return result;
}

