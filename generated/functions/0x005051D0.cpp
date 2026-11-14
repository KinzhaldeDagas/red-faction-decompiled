// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005051D0 rf_trigger_scan_entity
// UNREALRED VERIFIED [trigger-geometry-20261020] Ordinary explicit entity scan visits every non-auto trigger with caller mode. Current xrefs are player Use dispatcher4DA... sites4DB069/4DB5BE. Do not infer that this specific routine is the physical-pair driver; physical updates use4BE850 from4BFDF0.
// UNREALRED VERIFIED [trigger-inside-time-20261021] Every non-auto trigger reaches common query504B30 for this caller/mode, including geometry failures that can clear shared InsideTime. No Trigger Event/Inside/Auto display-name whitelist exists. Current UE player interaction still selects a nearby interaction; complete all-trigger Use scan and dedicated flag4 auto ownership remain separate adapter work.
// UNREALRED VERIFIED [trigger-use-20261021] Walks ALL non-auto runtime triggers in list order with current caller/mode; success sets aggregate handled=1 but never short-circuits. Distant/failed common queries can clear shared InsideTime. UnrealRed now scans source trigger order rather than nearest HUD component; this supersedes the older UE-adapter limitation in the InsideTime annotation.
char __cdecl rf_trigger_scan_entity(_DWORD *a1, char a2)
{
  int i; // [esp+0h] [ebp-8h]
  char v4; // [esp+7h] [ebp-1h]

  v4 = 0;
  for ( i = rf_trigger_runtime_list_head; (_UNKNOWN *)i != &unk_90B510; i = *(_DWORD *)(i + 652) )
  {
    if ( !rf_trigger_is_auto(i) && rf_trigger_test_entity_activation(i, a1, a2) == 1 )
      v4 = 1;
  }
  return v4;
}

