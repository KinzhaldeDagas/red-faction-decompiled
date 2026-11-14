// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005C2720 rf_d3d8_end_scene_shutdown_adapter
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, input remapping,text wrapping,Bink playback/default records,archive metadata,projection/aperture/classification and glass submission): No args: calls existing5C25F0 end-scene-if-active helper and returns. No own initialization/active flag check,device release,loop or extra cleanup. Called during backend shutdown. Existing void type retained.
void rf_d3d8_end_scene_shutdown_adapter()
{
  rf_d3d8_end_scene_if_active();
}

