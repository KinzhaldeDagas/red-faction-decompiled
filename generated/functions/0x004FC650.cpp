// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FC650 rf_event_defuse_nuke_apply
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type86 Defuse_Nuke. Call rf_ui_request_panel_deferred(24,0,0); no physics/explosion disarm, inventory or target traversal in this body.
int rf_event_defuse_nuke_apply()
{
  return rf_ui_request_panel_deferred(24, 0, 0);
}

