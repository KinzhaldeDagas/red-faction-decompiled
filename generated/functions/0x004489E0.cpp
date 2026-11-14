// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004489E0 rf_level_preload_render_and_effect_resources
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No arguments. Execute EXACT ordered calls477BF0 world face/lightmap texture binding,426600 live entity model/weapon-vclip preload,50D7D0 player-weapon
// impact-vclip preload,472FD0 item model material preparation,415C80 clutter primary/corpse model preparation,44ACB0 verified no-op,506D70 conditional liquid splash vclip
// preload,418260 verified no-op. This wrapper tests no result or readiness/level/player flag, performs no own resource traversal/allocation/state reset, and does not aggregate
// failures; individual helpers retain their native guards and partial effects. An earlier nonreturn/exception prevents later calls, with no wrapper rollback. Nominal void; EAX is
// final-delegate residue (last no-op does not normalize it), not count/success. Eight direct RF subsystem operations prove application ownership and false generic CRT classification
// independently of old name/comment.
void rf_level_preload_render_and_effect_resources()
{
  rf_world_bind_all_face_and_lightmap_textures();
  rf_entity_preload_live_model_and_weapon_vclips();
  rf_weapon_preload_all_player_weapon_impact_vclips();
  rf_item_models_prepare_materials();
  rf_clutter_prepare_primary_and_corpse_models();
  rf_hud_noop_callback_44ACB0();
  rf_vclip_preload_liquid_splashes_if_level_has_liquid();
  rf_hook_418260_noop();
}

