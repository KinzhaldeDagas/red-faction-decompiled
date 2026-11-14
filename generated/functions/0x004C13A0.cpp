// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004C13A0 rf_bolt_emitter_snapshot_collect
// UNREALRED VERIFIED [runtime-snapshots-blood-glass-20261028] Collect8-byte bolt-emitter records from rf_bolt_emitter_registry. Entry+0=dword emitter+0; entry+4=raw emitter byte+0x58. Export BYTE count; remaining padding not explicitly cleared. No bolt segments, particle resources or timers in this payload.
int __cdecl rf_bolt_emitter_snapshot_collect(int a1, _BYTE *a2)
{
  _DWORD **v2; // eax
  int result; // eax
  _DWORD *v4; // [esp+0h] [ebp-8h]
  int i; // [esp+4h] [ebp-4h]

  for ( i = 0; i < rf_receiver_get_first_dword(rf_bolt_emitter_registry); ++i )
  {
    v2 = (_DWORD **)sub_552200(rf_bolt_emitter_registry, i);
    v4 = *v2;
    *(_DWORD *)(a1 + 8 * i) = **v2;
    *(_BYTE *)(a1 + 8 * i + 4) = *((_BYTE *)v4 + 88);
  }
  result = rf_receiver_get_first_dword(rf_bolt_emitter_registry);
  *a2 = result;
  return result;
}

