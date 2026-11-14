// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593580 rf_vfile_get_open_slot_status
// UNREALRED VERIFIED [event-registry-crc-20261028]: If signed slot at this+272>=0, returns dword0x189CEBC + 32832*slot; negative slot returns0. No upper slot bound here.
int __thiscall rf_vfile_get_open_slot_status(_DWORD *this)
{
  if ( (int)*(this + 68) >= 0 )
    return unk_189CEBC[8208 * *(this + 68)];
  else
    return 0;
}

