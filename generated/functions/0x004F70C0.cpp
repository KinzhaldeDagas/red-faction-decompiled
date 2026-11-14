// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F70C0 rf_level_snapshot_construct_subobjects
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Construct level bounds subobjects, then fixed arrays:64 entity records stride536 at2272;64 item records stride80 at36576;128 movers stride96 at57440;64 decals stride100 at70184;8 projectiles stride152 at76584;16 blood marks stride18 at77800;32 corpses stride532 at78088;128 GeoMod records stride32 at95112. These are storage capacities, not proof all collector counts are bounded. No full100128-byte memset or initialization of every payload/padding byte.
char *__thiscall rf_level_snapshot_construct_subobjects(char *this)
{
  rf_level_snapshot_bounds_construct((int)this);
  rf_vector_construct_no_unwind(
    this + 2272,
    0x218u,
    64,
    (void *(__thiscall *)(void *))rf_entity_snapshot_record_construct);
  rf_vector_construct_no_unwind(this + 36576, 0x50u, 64, rf_common_snapshot_record_construct_wrapper);
  rf_vector_construct_no_unwind(this + 57440, 0x60u, 128, rf_common_snapshot_record_construct_wrapper);
  rf_vector_construct_no_unwind(
    this + 70184,
    0x64u,
    64,
    (void *(__thiscall *)(void *))rf_decal_snapshot_record_construct);
  rf_vector_construct_no_unwind(
    this + 76584,
    0x98u,
    8,
    (void *(__thiscall *)(void *))rf_projectile_snapshot_record_construct);
  rf_vector_construct_no_unwind(
    this + 77800,
    0x12u,
    16,
    (void *(__thiscall *)(void *))rf_blood_mark_snapshot_record_construct);
  rf_vector_construct_no_unwind(
    this + 78088,
    0x214u,
    32,
    (void *(__thiscall *)(void *))rf_corpse_snapshot_record_construct);
  rf_vector_construct_no_unwind(
    this + 95112,
    0x20u,
    128,
    (void *(__thiscall *)(void *))rf_geomod_snapshot_record_construct);
  return this;
}

