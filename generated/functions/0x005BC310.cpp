// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005BC310 rf_memory_find_byte
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, buffered text reader/writer branches, allocation callers and original-PE newline literal): Cdecl(buffer,int byte,size_t count),thin wrapper forwarding all arguments unchanged to CRT memchr and returning first matching pointer/NULL. Does not search beyond count,append terminator or allocate. Used for newline detection and recovered line reader.
void *__cdecl rf_memory_find_byte(void *Buf, int Val, size_t MaxCount)
{
  return memchr(Buf, Val, MaxCount);
}

