// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B5DD0 rf_scene_model_instance_draw_billboard_beam_adapter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Thiscall model state plus float timeline/render parameter,RET4. Forwards receiver and unchanged float to rf_renderer_material_billboard_or_beam_backend_wrapper, returns backend EAX. No local geometry,alpha,bitmap load or visibility work; parent selects this for definition flags801h.
int __thiscall rf_scene_model_instance_draw_billboard_beam_adapter(float *this, float a2)
{
  return rf_renderer_material_billboard_or_beam_backend_wrapper(this, a2);
}

