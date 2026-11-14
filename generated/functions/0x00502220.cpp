// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00502220 rf_mission_event_removed_uid_tracking_enable
// UNREALRED VERIFIED [event-lifecycle-20261028]: Sets global byte0x90B055=1. Does not clear existing removed-UID count or list.
void rf_mission_event_removed_uid_tracking_enable()
{
  unk_90B055 = 1;
}

