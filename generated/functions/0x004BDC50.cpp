// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004BDC50 rf_world_object_callback_light_query_gate
// UNREALRED VERIFIED [impact-callbacks-20261028]: Returns bool(global0x1C99890==0). Object callback submitter uses this result as lighting-query byte; exact semantic role of global is not established here. No state writes.
bool rf_world_object_callback_light_query_gate()
{
  return unk_1C99890 == 0;
}

