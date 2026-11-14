// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0053A310 rf_procedural_bitmap_pool_acquire
// UNREALRED VERIFIED [resource-pools-20261028]: Acquires first circular free record0x1426658, moves to active head0x142665C using links+8/+12, increments count0x1426660, writes slot index=(record-base0x14262D8)/56 to mandatory output. Exhaustion writes output-1 and returns0. Payload not initialized here; no null output guard.
int __cdecl rf_procedural_bitmap_pool_acquire(int *a1)
{
  int v2; // [esp+0h] [ebp-4h]

  v2 = unk_1426658;
  if ( unk_1426658 )
  {
    if ( *(_DWORD *)(unk_1426658 + 8) == unk_1426658 )
    {
      *(_DWORD *)(unk_1426658 + 8) = 0;
      *(_DWORD *)(v2 + 12) = 0;
      unk_1426658 = 0;
    }
    else
    {
      unk_1426658 = *(_DWORD *)(unk_1426658 + 8);
      *(_DWORD *)(*(_DWORD *)(v2 + 12) + 8) = *(_DWORD *)(v2 + 8);
      *(_DWORD *)(*(_DWORD *)(v2 + 8) + 12) = *(_DWORD *)(v2 + 12);
      *(_DWORD *)(v2 + 8) = 0;
      *(_DWORD *)(v2 + 12) = 0;
    }
    if ( unk_142665C )
    {
      *(_DWORD *)(v2 + 12) = *(_DWORD *)(unk_142665C + 12);
      *(_DWORD *)(v2 + 8) = unk_142665C;
      *(_DWORD *)(*(_DWORD *)(unk_142665C + 12) + 8) = v2;
      *(_DWORD *)(unk_142665C + 12) = v2;
    }
    else
    {
      *(_DWORD *)(v2 + 8) = v2;
      *(_DWORD *)(v2 + 12) = v2;
      unk_142665C = v2;
    }
    ++unk_1426660;
    *a1 = (v2 - (int)&unk_14262D8) / 56;
  }
  else
  {
    *a1 = -1;
  }
  return v2;
}

