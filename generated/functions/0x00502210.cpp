// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502210 rf_mission_event_removed_uid_tracking_disable
// UNREALRED VERIFIED [event-lifecycle-20261028]: Sets global byte0x90B055=0. Event unregister only appends removed UID when this byte is exactly1. Does not clear existing removed-UID count or list.
void rf_mission_event_removed_uid_tracking_disable()
{
  unk_90B055 = 0;
}

