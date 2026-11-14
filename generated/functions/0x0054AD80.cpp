// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054AD80 rf_scratch_arena_free_at_exit
// UNREALRED VERIFIED [resource-pools-20261028]: free(global base0x1426C70), sets base null. Does not reset cursor/end/owner-count or clear tracked owner back-pointers here.
void __cdecl rf_scratch_arena_free_at_exit()
{
  free(MEMORY[0x1426C70]);
  MEMORY[0x1426C70] = nullptr;
}

