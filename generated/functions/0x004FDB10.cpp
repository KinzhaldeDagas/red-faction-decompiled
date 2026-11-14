// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FDB10 rf_event_monitor_state_forward
// UNREALRED VERIFIED [alarm-monitor-slay-continuation-20261027] event_monitor_state forward callback, vtable0x63E2E4 slot+4. Search target vector for clutter whose descriptor+0x74 has bit8; configure record via0x417CA0(clutter+0x2C,event+0x2BC,byte+0x2C0,float+0x2B8). Then reset SAME stack loop index [ebp-8] to0 and scan entire target vector, attaching every resolved entity id to that monitor via0x417D80. Inner loop exhausts the outer index, so for a stable target list only the first qualifying monitor clutter is processed, even when no registered monitor record exists. No deduplication or ordinary mission forwarding in this body.
int __thiscall rf_event_monitor_state_forward(int this)
{
  int result; // eax
  int *v2; // eax
  int *v3; // eax
  int v5; // [esp+8h] [ebp-Ch]
  int i; // [esp+Ch] [ebp-8h]
  int v7; // [esp+10h] [ebp-4h]

  for ( i = 0; ; ++i )
  {
    result = rf_receiver_get_first_dword((void *)(this + 668));
    if ( i >= result )
      break;
    v2 = (int *)sub_552200((_DWORD *)(this + 668), i);
    v7 = rf_clutter_find_by_uid(*v2);
    if ( v7 )
    {
      if ( (*(_DWORD *)(*(_DWORD *)(v7 + 660) + 116) & 8) != 0 )
        rf_monitor_configure_record(
          *(_DWORD *)(v7 + 44),
          *(_DWORD *)(this + 700),
          *(_BYTE *)(this + 704),
          *(float *)(this + 696));
      else
        v7 = 0;
    }
    if ( v7 )
    {
      for ( i = 0; i < rf_receiver_get_first_dword((void *)(this + 668)); ++i )
      {
        v3 = (int *)sub_552200((_DWORD *)(this + 668), i);
        v5 = rf_entity_resolve_handle(*v3);
        if ( v5 )
          rf_monitor_append_entity_identifier(*(_DWORD *)(v7 + 44), *(_DWORD *)(v5 + 44));
      }
    }
  }
  return result;
}

