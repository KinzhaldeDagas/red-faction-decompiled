// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0041B960 rf_glare_unlink_runtime_record
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, debris/solid ownership, glare definitions and runtime factories, native render admission and x87 unordered gates): Cdecl glare. Writes prev->next and next->prev using next+696/prev+700, then zeros both links and returns glare pointer bits. No containing allocation free, definition/bitmap destruction, object deletion mark, count update or duplicate-unlink guard. Requires valid linked neighbors.
int __cdecl rf_glare_unlink_runtime_record(int a1)
{
  *(_DWORD *)(*(_DWORD *)(a1 + 700) + 696) = *(_DWORD *)(a1 + 696);
  *(_DWORD *)(*(_DWORD *)(a1 + 696) + 700) = *(_DWORD *)(a1 + 700);
  *(_DWORD *)(a1 + 696) = 0;
  *(_DWORD *)(a1 + 700) = 0;
  return a1;
}

