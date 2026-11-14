// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0640 rf_binary_stream_write_word_host_order
// UNREALRED VERIFIED [image-headers-20261028]: This is stream object; one stack16-bit argument. Passes address and size2 to0x5A0990, returning its result. Stores host little-endian bytes in this x86 binary; no explicit swap, range or write-status check. Actual stream pointer passed in ECX despite incomplete caller decompilation.
int __thiscall rf_binary_stream_write_word_host_order(void *stream, unsigned __int16 value)
{
  return (int)rf_vfile_write_bytes_with_optional_feedback(stream, &value, 2u);
}

