// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0048ABB0 rf_mover_stop_by_uid
// UNREALRED VERIFIED [mission-mover-activation-20261013] Stop by mover UID, NOT direction reversal. With flags+0x318 bit0x40, OR bit0x20 and zero ramp clock+0x308; do not clear ramp-up bit0x10 or target index. Otherwise call empty helper0x48AC30 and set target+0x2FC=-1. Both paths set speed+0x2F4=0. No sound-stop call and no position/elapsed/distance reset.
int __cdecl rf_mover_stop_by_uid(int a1)
{
  int result; // eax
  int v2; // [esp+0h] [ebp-4h]

  result = rf_mover_resolve_handle(a1);
  v2 = result;
  if ( result )
  {
    if ( (*(_DWORD *)(result + 792) & 0x40) != 0 )
    {
      *(_DWORD *)(result + 792) |= 0x20u;
      *(float *)(result + 776) = 0.0;
    }
    else
    {
      rf_mover_stop_noop();
      *(_DWORD *)(v2 + 764) = -1;
    }
    *(float *)(v2 + 756) = 0.0;
    return v2;
  }
  return result;
}

