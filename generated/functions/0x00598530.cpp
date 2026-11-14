// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00598530 rf_file_transfer_record_destroy
// UNREALRED VERIFIED [file-transfer-20261028]: Thiscall destructor invokes virtual-file destructor on member+132 only. Does not call transfer protocol cleanup, release a slot explicitly or send packets.
void __thiscall rf_file_transfer_record_destroy(int *this)
{
  rf_vfile_destruct_close_if_open(this + 33);
}

