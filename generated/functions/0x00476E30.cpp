// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00476E30 rf_cutscene_camera_record_construct
// UNREALRED VERIFIED [cutscene-playback-20261028]: Calls default vector constructor0x4F2700 on record+4 and returns record. That helper performs no memory writes, so this body does NOT initialize position floats, identifier or orientation. Caller/load code must populate them.
int __thiscall rf_cutscene_camera_record_construct(int this)
{
  rf_vector3_default_construct_noop((void *)(this + 4));
  return this;
}

