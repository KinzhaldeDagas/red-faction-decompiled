// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B5E10 rf_scene_model_instance_draw_chne_ribbon
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Thiscall model state. Tests lengthSquared of render position80 against0; only nonzero case pushes renderer instance transform(position80,matrix92), and same condition later pops. Orientation alone does not trigger push. Constructs local212-byte ribbon descriptor via5B7F50, which actually leaves bytes unchanged. Sets count0=definition.vertexCount176,texture196=definition.handle272,width200=definition.float268, then copies ALL runtime vertices128 at12-byte stride into inline points starting+4. Point array is16 elements but count is NOT capped: vertex index16 overwrites descriptor texture/width/aux fields, larger counts overrun local descriptor. Passes descriptor and shared particle-glow render-state value to
// polyline-ribbon bridge57FC90 (backend102 only). No count/handle/pointer validation, line subdivision or initialization of remaining descriptor fields. EAX false0 when no transform push, otherwise renderer-pop result; no consistent draw status.
int __thiscall rf_scene_model_instance_draw_chne_ribbon(float *this)
{
  int result; // eax
  float copy_result[3]; // [esp+4h] [ebp-E8h] BYREF
  int i; // [esp+10h] [ebp-DCh]
  _DWORD v5[53]; // [esp+14h] [ebp-D8h] BYREF
  bool v6; // [esp+EBh] [ebp-1h]

  v6 = rf_vector_length_squared(this + 20) != 0.0;
  if ( v6 )
    rf_renderer_push_instance_transform_dispatch((int)(this + 20), (int)(this + 23));
  rf_ribbon_descriptor_construct_points_noop((char *)v5);
  v5[0] = *(_DWORD *)(*(_DWORD *)this + 176);
  v5[49] = *(_DWORD *)(*(_DWORD *)this + 272);
  *(float *)&v5[50] = *(float *)(*(_DWORD *)this + 268);
  for ( i = 0; i < *(_DWORD *)(*(_DWORD *)this + 176); ++i )
    rf_vector_copy((float *)&v5[3 * i + 1], copy_result, (const float *)(*((_DWORD *)this + 32) + 12 * i));
  rf_renderer_polyline_ribbon_backend_wrapper((int)v5, SLODWORD(rf_particle_glow_billboard_render_state));
  result = v6;
  if ( v6 )
    return rf_renderer_pop_instance_transform_dispatch();
  return result;
}

