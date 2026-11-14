// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054AD20 rf_scratch_arena_allocate
// UNREALRED VERIFIED [resource-pools-20261028]: malloc(Size) to global0x1426C70; failure returns-1. Success sets cursor0x1482004=base,end0x1482000=base+Size, owner-count0x1426C74=0 and registers0x54AD80 at exit, returns0. Does not free prior arena before overwriting base.
int __cdecl rf_scratch_arena_allocate(size_t Size)
{
  MEMORY[0x1426C70] = malloc(Size);
  if ( !MEMORY[0x1426C70] )
    return -1;
  unk_1482004 = MEMORY[0x1426C70];
  unk_1482000 = (char *)MEMORY[0x1426C70] + Size;
  unk_1426C74 = 0;
  atexit(rf_scratch_arena_free_at_exit);
  return 0;
}

