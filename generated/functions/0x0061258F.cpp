// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061258F __heap_init
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Cdecl(raw flag), calls HeapCreate(options=(flag==0
// ?1:0), initial4096, maximum0). Unconditionally replace global heap handle2021854 with returned handle, includingNULL. Failure returns0 and leaves heap mode2021F40 unchanged.
// Success stores heap mode1 and returns1, not the heap handle. No existing-handle guard/HeapDestroy/lock, small-block setup, errno mapping or retry; mode3 paths elsewhere are not
// selected by successful initialization here.
int __cdecl _heap_init(int a1)
{
  int result; // eax

  result = (int)HeapCreate(a1 == 0, 0x1000u, 0);
  MEMORY[0x2021854] = (HANDLE)result;
  if ( result )
  {
    unk_2021F40 = 1;
    return 1;
  }
  return result;
}

