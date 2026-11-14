// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00593540 rf_vfile_is_position_at_or_past_end_signed
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, command-line option ownership, loose lookup return semantics, VPP location, stream flags/status and file-attribute paths): Thiscall open VFile. Returns AL(slot DWORD+16 current position >= slot DWORD+28 length) using SIGNED comparison (SETNL593573). Does not call feof, examine I/O status or distinguish EOF from beyond-end seek. No open/index validation; negative/overflowed counters follow signed ordering.
bool __thiscall rf_vfile_is_position_at_or_past_end_signed(_DWORD *this)
{
  return unk_189CEC0[8208 * *(this + 68)] >= unk_189CECC[8208 * *(this + 68)];
}

