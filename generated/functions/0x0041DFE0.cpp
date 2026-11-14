// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041DFE0 rf_corpse_update_animation
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, corpse factory/support/drop lifecycle, fixed-stride snapshot boundaries and existing-object restoration, record24 ownership and native decal ABI): Cdecl corpse. ONLY ordered health52<0 ORs common delete mask2 and returns; unordered health enters normal path. Exact retiring result1 decrements fade664 by frame delta and marks deletion only on ordered fade<=0, not NaN. Exact elapsed timer684 result1 invalidates timer and walks emitter616/next336 clearing active BYTE320; no emitter unlink/free. Ordered scalar688>0 decreases by frameDelta/500 times class-indexed5396-stride float, without lower clamp. Signed death action696>=0 plus corpse flag8 resets cyclic model, starts held action, advances FULL duration then another0.30000001192092896, clears mask8 and refreshes sphere geometry. Associated item716!=-1 resolves item,
// computes corpse node/world position, writes item predicted position+240 and publishes via4BC330; missing item leaves UID unchanged. Nonnull model128 finally updates VFX by frame delta with corpse pose60/72 and final flag1. Does not return uniform status, stop after marking deletion, reset action list globally, validate model/class/index or initialize absent item fields.
int *__cdecl rf_corpse_update_animation(int a1)
{
  int *result; // eax
  float copy_result[3]; // [esp+14h] [ebp-24h] BYREF
  float source[3]; // [esp+20h] [ebp-18h] BYREF
  int *v4; // [esp+2Ch] [ebp-Ch]
  float v5; // [esp+30h] [ebp-8h]
  int i; // [esp+34h] [ebp-4h]

  if ( *(float *)(a1 + 52) >= 0.0 )
  {
    if ( (unsigned __int8)rf_corpse_is_retiring(a1) == 1 )
    {
      *(float *)(a1 + 664) = *(float *)(a1 + 664) - rf_frame_delta_seconds;
      if ( *(float *)(a1 + 664) <= 0.0 )
        rf_object_mark_for_deferred_delete(a1);
    }
    if ( rf_replicator_has_elapsed((int *)(a1 + 684)) )
    {
      rf_timestamp4_invalidate((_DWORD *)(a1 + 684));
      for ( i = *(_DWORD *)(a1 + 616); i; i = *(_DWORD *)(i + 336) )
        *(_BYTE *)(i + 320) = 0;
    }
    if ( *(float *)(a1 + 688) > 0.0 )
      *(float *)(a1 + 688) = *(float *)(a1 + 688)
                           - rf_frame_delta_seconds / 500.0 * flt_68492C[1349 * *(_DWORD *)(a1 + 672)];
    if ( *(int *)(a1 + 696) >= 0 && (*(_DWORD *)(a1 + 668) & 8) != 0 )
    {
      rf_model_handle_reset_cyclic_adapter(*(_DWORD *)(a1 + 128));
      rf_vfx_start_instance(*(int **)(a1 + 128), *(_DWORD *)(a1 + 696), 1.0, 1);
      v5 = rf_model_animation_duration_seconds((unsigned int *)*(_DWORD *)(a1 + 128), *(_DWORD *)(a1 + 696));
      rf_vfx_update_instance(*(int **)(a1 + 128), v5, 0, 0, 0, 1);
      rf_vfx_update_instance(*(int **)(a1 + 128), 0.30000001, 0, 0, 0, 1);
      *(_DWORD *)(a1 + 668) &= ~8u;
      rf_corpse_refresh_vmesh_geometry(a1);
    }
    result = (int *)a1;
    if ( *(_DWORD *)(a1 + 716) != -1 )
    {
      result = (int *)rf_item_resolve_handle(*(_DWORD *)(a1 + 716));
      v4 = result;
      if ( result )
      {
        rf_vector3_default_construct_noop(source);
        rf_object_copy_node_or_common_world_position(a1, (int)source);
        rf_vector_copy((float *)v4 + 60, copy_result, source);
        result = (int *)rf_object_publish_position_and_bounds((int)v4, source);
      }
    }
    if ( *(_DWORD *)(a1 + 128) )
      return rf_vfx_update_instance(*(int **)(a1 + 128), rf_frame_delta_seconds, 0, a1 + 60, a1 + 72, 1);
  }
  else
  {
    *(_DWORD *)(a1 + 124) |= 2u;
    return (int *)a1;
  }
  return result;
}

