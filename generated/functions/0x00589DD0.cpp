// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00589DD0 rf_model_mesh144_deleting_destructor
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character-cache callers, resource readers and constructor/destructor paths): MSVC scalar/vector deleting-destructor adapter for144-byte mesh records. Flags bit2 selects array destruction using count cookie at this-4 and stride144, else calls mesh destructor5B8290 once. Flags bit1 additionally frees allocation (array cookie base for arrays, object for scalar). Returns that base even if freed. Does not validate cookie/count or clear caller pointer.
char *__thiscall rf_model_mesh144_deleting_destructor(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(
      this,
      0x90u,
      *((_DWORD *)this - 1),
      (void (__thiscall *)(void *))rf_model_mesh144_destroy_lod_table);
    if ( (a2 & 1) != 0 )
      operator delete(this - 4);
    return this - 4;
  }
  else
  {
    rf_model_mesh144_destroy_lod_table(this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

