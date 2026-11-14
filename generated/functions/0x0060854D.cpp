// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060854D __unlink
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native tail alias: unlink forwards original path to remove. Hotpatch/frame setup is fully undone BEFORE tail JMP0060851D _remove. Caller-supplied stack
// slots/return address unchanged; no extra argument push, receiver dereference, allocation, own pointer/NULL validation or result normalization. Delegate receives original ABI and
// returns directly to original caller. This body adds no independent implementation or storage cleanup.
int __cdecl _unlink(const char *FileName)
{
  return remove(FileName);
}

