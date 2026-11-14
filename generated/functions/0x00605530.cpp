// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00605530 rf_jpeg_master_pass_startup
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jcmaster.c:pass_startup matched): Clears master.call_pass_startup and writes the frame header followed by scan header. This deferred startup permits application markers between SOI and SOF/SOS. Does not consume input rows.
int __cdecl rf_jpeg_master_pass_startup(int a1)
{
  *(_DWORD *)(*(_DWORD *)(a1 + 328) + 12) = 0;
  (*(void (__cdecl **)(int))(*(_DWORD *)(a1 + 344) + 4))(a1);
  return (*(int (__cdecl **)(int))(*(_DWORD *)(a1 + 344) + 8))(a1);
}

