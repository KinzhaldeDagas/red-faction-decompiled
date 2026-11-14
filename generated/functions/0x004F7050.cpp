// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7050 rf_savegame_player_record_construct
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Invoke default vector constructor at+64, matrix constructor+116, default vector+152. Observed default vector0x4F2700 is no-op and matrix constructor uses no-op row constructors. No player-name, flag, scalar, inventory-array or whole-subrecord clearing in this body.
char *__thiscall rf_savegame_player_record_construct(char *this)
{
  rf_vector3_default_construct_noop(this + 64);
  rf_matrix3_construct(this + 116);
  rf_vector3_default_construct_noop(this + 152);
  return this;
}

