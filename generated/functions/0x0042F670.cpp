// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0042F670 sub_42F670
// UNREALRED VERIFIED [combat-speech-eye-phase-20261111]: Eye/cache preparation is once per MODEL CLASS+29C, guarded class+724 bit40000000;42F6C0 itself sets it and this caller sets it again. Therefore first class initialization wins across body instances. Host source/mesh resource changes may invalidate backend views but ordinary body/directive/animation refresh must not silently create a new per-body native class cache.
int *__cdecl sub_42F670(int *a1)
{
  int *result; // eax

  result = a1;
  if ( (*(_DWORD *)(a1[167] + 1828) & 0x40000000) == 0 )
  {
    sub_42F6C0(a1);
    result = (int *)(*(_DWORD *)(a1[167] + 1828) | 0x40000000);
    *(_DWORD *)(a1[167] + 1828) = result;
  }
  return result;
}

