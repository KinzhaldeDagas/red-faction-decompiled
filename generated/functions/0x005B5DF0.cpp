// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B5DF0 rf_scene_model_instance_draw_mesh_faces_adapter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Thiscall model state and float parameter,RET4. Directly returns rf_renderer_submit_mesh_faces(receiver,float); no buffer allocation,geometry update,visibility test or local material loop. Parent selects this only for subtype0 without flags801h.
int __thiscall rf_scene_model_instance_draw_mesh_faces_adapter(_DWORD *this, float a2)
{
  return rf_renderer_submit_mesh_faces(this, a2);
}

