// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417740 rf_monitor_update_records_for_player
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, monitor lifetime, debris lifecycle/contact audio, native render ABI and mixed spawn descriptor): Cdecl player pointer; walks the intrusive monitor list until sentinel &0x6807E4. Caches each record next pointer BEFORE calling 0x417780, permitting removal/free of the current record. Does not snapshot other mutations, validate player/list or provide a defined result.
void __cdecl rf_monitor_update_records_for_player(int a1)
{
  _DWORD *v1; // [esp+0h] [ebp-8h]
  _DWORD *i; // [esp+4h] [ebp-4h]

  for ( i = (_DWORD *)dword_6807E4; i != &dword_6807E4; i = v1 )
  {
    v1 = (_DWORD *)*i;
    rf_monitor_update_record_render_or_remove_stale(a1, i);
  }
}

