// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00423520 rf_entity_initialize_definitions_and_shared_effect_resources
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, entity action/weapon transforms, definition resource teardown and native byte/x87/partial-output behavior and
// native signed/x87/stack/callback ABI): No args; resets global DWORDs681E14(definition count),681E10,681E70=0, then423670 entity.tbl load. After return sets681E38=0 and
// both68211C/682120=&681E90 (native XOR EAX,EAX/JNZ makes shown back-edge unreachable, not a live loop). Load Light_lilredflare01.tga→681E68 and Light_lilgreenflare01.tga→681E20 with
// raw(filename,-1,1), then warm-bind each unconditionally. Call43D240 blood resources init and4401A0, the latter only resolves literal Broken Glass Footstep foley index into661570
// despite inherited false CRT name. Set681E64,681E74,681E24=-1; lookup Sub Hit foley into681E18. Load powerup-invuln.vbm→661308,powerup-damage.vbm→66130C with same(-1,1), bind both;
// load glograd.tga→661310, bind it. Finally register426030 cleanup with atexit and return its exact EAX status, not resource/parse success. No resource-return predicates or rollback:
// failed resource handles are stored and passed to warmup; repeated calls add exit registrations and overwrite globals without own prior-resource teardown.
// UNREALRED VERIFIED [original-target-scan-list-lifetime-20261112]: Startup sets head68211C and tail682120 to sentinel681E90.42CB80 appends at42EE37..42EE83; this is BEFORE constructor tail (e.g13FC Arm(-1000) at42F124), so completed-constructor host publication is not proof of exact native callback phase. Entity death/inactive predicates do not themselves unlink the native entity list.
int rf_entity_initialize_definitions_and_shared_effect_resources()
{
  unk_681E14 = 0;
  unk_681E10 = 0;
  unk_681E70 = 0;
  rf_entity_load_entity_tbl_definitions();
  dword_681E38 = 0;
  unk_68211C = &unk_681E90;
  unk_682120 = &unk_681E90;
  dword_681E68 = rf_bitmap_load_with_optional_mipmap_generation("Light_lilredflare01.tga", (void *)0xFFFFFFFF, 1);
  dword_681E20 = rf_bitmap_load_with_optional_mipmap_generation("Light_lilgreenflare01.tga", (void *)0xFFFFFFFF, 1);
  rf_renderer_bind_texture_for_level_warmup(dword_681E68);
  rf_renderer_bind_texture_for_level_warmup(dword_681E20);
  rf_blood_effect_resources_init();
  rf_foley_cache_broken_glass_footstep_index();
  unk_681E64 = -1;
  unk_681E74 = -1;
  unk_681E24 = -1;
  unk_681E18 = rf_foley_definition_find_name("Sub Hit");
  dword_661308 = rf_bitmap_load_with_optional_mipmap_generation("powerup-invuln.vbm", (void *)0xFFFFFFFF, 1);
  dword_66130C = rf_bitmap_load_with_optional_mipmap_generation("powerup-damage.vbm", (void *)0xFFFFFFFF, 1);
  rf_renderer_bind_texture_for_level_warmup(dword_661308);
  rf_renderer_bind_texture_for_level_warmup(dword_66130C);
  dword_661310 = rf_bitmap_load_with_optional_mipmap_generation("glograd.tga", (void *)0xFFFFFFFF, 1);
  rf_renderer_bind_texture_for_level_warmup(dword_661310);
  return atexit(rf_entity_definitions_clear_strings_and_action_arrays);
}

