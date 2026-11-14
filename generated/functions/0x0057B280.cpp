// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057B280 rf_crc32_accumulator_construct_zero
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, parser enum/CRC contracts, output formatting, root/media path construction, VPP buffer reads and lookup lifecycle): Thiscall DWORD accumulator. Writes0 to receiver[0] and returns receiver. Called for local CRC state by parser57A990 and rf_vfile_compute_raw_crc32 (call at593A0A); does not build polynomial table, process bytes, useFFFFFFFF seed or final-complement state. Existing library flag retained.
_DWORD *__thiscall rf_crc32_accumulator_construct_zero(_DWORD *this)
{
  *this = 0;
  return this;
}

