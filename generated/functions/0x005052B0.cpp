// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005052B0 rf_trigger_commit_flag8_triggers
// UNREALRED VERIFIED [mission-startup-20261020] Startup scans trigger list in creation order, selecting flag0x08 and not disabled0x10, then directly commits with activating entity -1 and mover suppression0. No ordinary eligibility check: finite counts, cooldown, explicit-use, containment and InsideTime do not gate this call. Earlier links can enable a later startup trigger before its turn. Flag0x04 is unrelated dedicated auto-Use ownership.
char rf_trigger_commit_flag8_triggers()
{
  int v0; // eax
  int i; // [esp+0h] [ebp-4h]

  if ( unk_90B508 == 1 )
  {
    LOBYTE(v0) = rf_trigger_filter_flag8_links();
  }
  else
  {
    LOBYTE(v0) = rf_trigger_runtime_list_head;
    for ( i = rf_trigger_runtime_list_head; (_UNKNOWN *)i != &unk_90B510; i = *(_DWORD *)(i + 652) )
    {
      LOBYTE(v0) = i;
      if ( (*(_DWORD *)(i + 688) & 8) != 0 )
      {
        v0 = *(_DWORD *)(i + 688) & 0x10;
        if ( !v0 )
          LOBYTE(v0) = rf_trigger_commit_activation(i, -1, 0, 0);
      }
    }
  }
  return v0;
}

