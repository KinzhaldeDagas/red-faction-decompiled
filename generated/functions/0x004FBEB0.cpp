// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004FBEB0 rf_event_win_ps2_demo_apply
// UNREALRED VERIFIED [generic-mission-event-continuation-20261027] Generic forward type68 Win_PS2_Demo. Call rf_ui_request_panel_deferred(21,0,0). No console platform check, target traversal or immediate panel rendering in this body.
int rf_event_win_ps2_demo_apply()
{
  return rf_ui_request_panel_deferred(21, 0, 0);
}

