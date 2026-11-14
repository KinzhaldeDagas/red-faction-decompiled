// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005E6BB0 rf_pcx_write_rle_packet
// UNREALRED VERIFIED [image-headers-20261028]: Actual THREE stack arguments pixel byte,repeat-count byte,stream pointer (last omitted by current decompiler). Count0 returns0, no write. Count1 and pixel top bits!=0xC0 writes literal and returns1. Otherwise writes count|0xC0 then pixel, returns2. Uses stream pointer in ECX for0x5A05F0. Ignores both underlying write results; return counts intended bytes, not successful I/O. No repeat<=63 validation; caller0x5E6A90 bounds runs.
int __cdecl rf_pcx_write_rle_packet(char a1, char a2, _DWORD *a3)
{
  if ( !a2 )
    return 0;
  if ( a2 != 1 || (a1 & 0xC0) == 0xC0 )
  {
    rf_binary_stream_write_byte_host_order(a3, a2 | 0xC0);
    rf_binary_stream_write_byte_host_order(a3, a1);
    return 2;
  }
  else
  {
    rf_binary_stream_write_byte_host_order(a3, a1);
    return 1;
  }
}

