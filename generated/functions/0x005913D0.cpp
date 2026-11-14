// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005913D0 rf_dsound_get_property_interface_pointer
// UNREALRED VERIFIED [dsound-buffers-20261028]: Returns global property-interface pointer0x19514D4 unchanged. Borrowed pointer; no AddRef or capability query.
int rf_dsound_get_property_interface_pointer()
{
  return dword_19514D4;
}

