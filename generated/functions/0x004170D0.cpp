// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004170D0 rf_clutter_skin108_deleting_destructor
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, clutter registry grammar/default retention,108-byte skin ownership, allocator cookies, native stack aliases and original flag-table strings): Thiscall usable record/array pointer plus low-byteflags,RET4. flags&2:reads cookieDWORD(this-4),destroys that many108-byte records with416DB0;flags&1 additionally operator-deletes(this-4);returns(this-4) regardlessfree. Without flag2,destroys ONE record,optionally operator-deletes(this) when flag1,andreturns this. Does not consult owning array logicalcount/capacity or NULL-check receiver/cookie;array mode must receive usablebase after4-byte cookie.
char *__thiscall rf_clutter_skin108_deleting_destructor(char *this, char a2)
{
  if ( (a2 & 2) != 0 )
  {
    `eh vector destructor iterator'(
      this,
      0x6Cu,
      *((_DWORD *)this - 1),
      (void (__thiscall *)(void *))rf_clutter_skin108_destroy_strings);
    if ( (a2 & 1) != 0 )
      operator delete(this - 4);
    return this - 4;
  }
  else
  {
    rf_clutter_skin108_destroy_strings(this);
    if ( (a2 & 1) != 0 )
      operator delete(this);
    return this;
  }
}

