// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00410750 rf_path_record_enqueue_unmarked_neighbors
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, AI route geometry, camera state and entity member lifecycle, native floating-point branches/rounding and SEH
// cleanup and native signed/x87/stack/callback ABI): Cdecl(required path record pointer); mutates shared queue666438/count6665D0 and neighbor BYTE+52. Signed i0..<DWORD[record+40]
// re-reads neighbor array count each iteration; unchecked element helper uses backing DWORD+8+4*i. For each neighbor, ANY nonzero BYTE+52 skips. Zero marker is set EXACT1 BEFORE
// writing neighbor pointer to queue666438[queueCount], then increments wrapped32 queue count, THEN exits if signed new count>=102. No pre-write ceiling check: standalone entry with
// count>=102 can write beyond queue before stopping, and initial negative count is not guarded. Already-marked neighbors do not trigger ceiling check. Normal410340 caller starts
// expansion with count<limit<=100. No requested-limit argument, recursion, point generation, eligibility test, marker rollback or pointer guard. EAX is incidental: current
// count-getter value on natural exhaustion, old queue count on capacity exit; not a bool/status.
int __cdecl rf_path_record_enqueue_unmarked_neighbors(int a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(a1 + 40));
    if ( i >= result )
      break;
    v2 = *(_DWORD *)sub_552200((_DWORD *)(a1 + 40), i);
    if ( !*(_BYTE *)(v2 + 52) )
    {
      *(_BYTE *)(v2 + 52) = 1;
      result = unk_6665D0;
      dword_666438[unk_6665D0++] = v2;
      if ( unk_6665D0 >= 102 )
        break;
    }
  }
  return result;
}

