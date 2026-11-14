// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00590F40 rf_dsound_resume_slot_from_cached_flags
// UNREALRED VERIFIED [dsound-buffers-20261028]: Argument slot. Calls DS Play+48 with reserved0,priority0,flags bool(cached flags+40 &5),then clears pause mask2 regardless HRESULT. Masks1/4 both imply looping flag1. Returns44*slot offset,not Play result. No buffer null/index checks or cursor reset.
int __cdecl rf_dsound_resume_slot_from_cached_flags(int a1)
{
  (*(void (__stdcall **)(int, _DWORD, _DWORD, bool))(*(_DWORD *)unk_1BA1820[11 * a1] + 48))(
    unk_1BA1820[11 * a1],
    0,
    0,
    (unk_1BA1848[11 * a1] & 5) != 0);
  unk_1BA1848[11 * a1] &= ~2u;
  return 44 * a1;
}

