// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005951C0 rf_progress_register_or_finish_callback
// UNREALRED VERIFIED [system-progress-20261028]: Arguments callback,positive-count-trigger control,input-poll byte. Nonnull callback resets invocation count0x1BC2154 and last-dispatched count0x1BC2158, stores control0x664798, sets deadline0x664794=elapsedMillis+100, stores callback0x1BC214C, increments reentrancy counter0x1BC2150 around immediate callback(0,0,0). Null callback invokes PREVIOUS callback(-1,0,0) under reentrancy counter WITHOUT checking it is nonnull; then deadline=-1 and callback=null. Finally stores input-poll byte0x1BC2148,clears sticky abort0x1BC2149 and returns invocation count. No nested-registration ownership or callback-result handling.
int __cdecl rf_progress_register_or_finish_callback(int (__cdecl *a1)(_DWORD, _DWORD, _DWORD), int a2, char a3)
{
  if ( a1 )
  {
    unk_1BC2154 = 0;
    unk_1BC2158 = 0;
    dword_664798 = a2;
    dword_664794 = rf_performance_clock_elapsed_scaled(1000) + 100;
    unk_1BC214C = a1;
    ++unk_1BC2150;
    a1(0, 0, 0);
    --unk_1BC2150;
  }
  else
  {
    ++unk_1BC2150;
    unk_1BC214C(-1, 0, 0);
    --unk_1BC2150;
    dword_664794 = -1;
    unk_1BC214C = nullptr;
  }
  unk_1BC2148 = a3;
  unk_1BC2149 = 0;
  return unk_1BC2154;
}

