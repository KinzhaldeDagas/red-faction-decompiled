// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B5DB0 rf_scene_model_instance_draw_glow_adapter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Thiscall model-state pointer. Directly forwards receiver to rf_renderer_glow_billboard_backend_wrapper and returns its EAX. No local visibility,handle,backend,transform or resource checks; dispatcher5B5CD0 gates on positive definition handle272.
int __thiscall rf_scene_model_instance_draw_glow_adapter(float *this)
{
  return rf_renderer_glow_billboard_backend_wrapper(this);
}

