// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004F73A0 rf_savegame_cache_construct_subobjects
// UNREALRED VERIFIED [event-registry-crc-20261028]: Constructs83544-byte save header at this, then four level-snapshot subobjects of100128 bytes starting this+83544. Total484056 bytes. Only delegates subobject constructors; does not zero full cache. Returns this.
char *__thiscall rf_savegame_cache_construct_subobjects(char *this)
{
  rf_savegame_header_construct_subobjects(this);
  rf_vector_construct_no_unwind(
    this + 83544,
    0x18720u,
    4,
    (void *(__thiscall *)(void *))rf_level_snapshot_construct_subobjects);
  return this;
}

