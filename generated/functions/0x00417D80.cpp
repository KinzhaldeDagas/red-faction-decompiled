// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00417D80 rf_monitor_append_entity_identifier
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] Find registered monitor; absent is no-op. Append supplied entity identifier to vector+0x18 without a uniqueness check. Resolve entity: when resolution succeeds and rf_entity_is_nonplayer_sentient_or_runtime_enabled returns false, write entity numeric state+0x520=15. If monitor selected id+0x10 is -1, assign supplied identifier even when entity resolution failed. Does not rearm timer or force render-state refresh.
int *__cdecl rf_monitor_append_entity_identifier(int a1, int a2)
{
  int *result; // eax
  int v3; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  result = rf_monitor_find_record(a1);
  v4 = (int)result;
  if ( result )
  {
    rf_pointer_array_append_dword(result + 6, a2);
    v3 = rf_entity_resolve_handle(a2);
    if ( v3 && !rf_entity_is_nonplayer_sentient_or_runtime_enabled(v3) )
      *(_DWORD *)(v3 + 1312) = 15;
    result = (int *)v4;
    if ( *(_DWORD *)(v4 + 16) == -1 )
      *(_DWORD *)(v4 + 16) = a2;
  }
  return result;
}

