// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005B5F40 rf_scene_model_instance_update_geometry_adapter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, model152 binding/update/draw, temporal/visibility edges, transform ordering, ribbon bounds and vector-result ABI): Thiscall model state and one float timeline in15Hz units,RET4. Forwards ECX receiver and stack float to5B5F60 only. Scene update5CDB90 calls for152-byte model states and ignores return. Declared void to avoid assigning semantic result to main updater register residue; no time conversion,visibility or resource logic in adapter.
void __thiscall rf_scene_model_instance_update_geometry_adapter(char *self, float timeline15)
{
  rf_scene_model_instance_update_geometry(self, timeline15);
}

