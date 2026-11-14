// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A05F0 rf_binary_stream_write_byte_host_order
// UNREALRED VERIFIED [image-headers-20261028]: This is vfile/binary-stream object; one stack byte argument. Passes address of local byte and size1 to0x5A0990, returns its result. Actual thiscall stream pointer is omitted from several current caller decompilations but is present in ECX in assembly. No independent status validation or endian conversion.
int *__thiscall rf_binary_stream_write_byte_host_order(_DWORD *this, char Buffer)
{
  return rf_vfile_write_bytes_with_optional_feedback(this, &Buffer, 1u);
}

