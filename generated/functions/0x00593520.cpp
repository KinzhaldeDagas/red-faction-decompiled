// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593520 rf_vfile_get_open_slot_offset
// UNREALRED VERIFIED [event-registry-crc-20261028]: Directly returns dword0x189CEC0 + 32832*slot, where slot is signed dword at this+272. No slot validity check in this body; caller must provide open VFile.
int __thiscall rf_vfile_get_open_slot_offset(_DWORD *this)
{
  return unk_189CEC0[8208 * *(this + 68)];
}

