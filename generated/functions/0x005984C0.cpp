// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005984C0 rf_file_transfer_record_construct
// UNREALRED VERIFIED [file-transfer-20261028]: Thiscall partial constructor: virtual-file member at+132 and Replicator member at+424. Returns this. Does not explicitly clear flags, names, byte counters, peer, selector or transfer ID; no allocation or transfer start.
int *__thiscall rf_file_transfer_record_construct(int *this)
{
  rf_vfile_construct_unopened(this + 33);
  rf_timestamp4_construct_invalid(this + 106);
  return this;
}

