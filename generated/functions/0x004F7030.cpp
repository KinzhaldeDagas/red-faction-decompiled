// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F7030 rf_savegame_header_construct_subobjects
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Construct save-header player subrecord only at this+62232 using0x4F7050. Does not initialize header tag/count/current index, names, music, persona-history bytes or whole83544-byte block to zero.
char *__thiscall rf_savegame_header_construct_subobjects(char *this)
{
  rf_savegame_player_record_construct(this + 62232);
  return this;
}

