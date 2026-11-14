// IDA pseudocode evidence; not yet portable or build-ready.
// 0x006060E9 ??3@YAXPAX@Z
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): Native tail alias: operator delete forwards raw pointer to free. Hotpatch/frame setup is fully undone BEFORE tail JMP00606D56 _free. Caller-supplied stack
// slots/return address unchanged; no extra argument push, receiver dereference, allocation, own pointer/NULL validation or result normalization. Delegate receives original ABI and
// returns directly to original caller. This body adds no independent implementation or storage cleanup.
void __cdecl operator delete(void *Block)
{
  free(Block);
}

