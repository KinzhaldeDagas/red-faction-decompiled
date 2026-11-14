// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0670 rf_binary_stream_write_int32_host_order
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,32-bit stack value. Passes address of argument,count4 to0x5A0990. No endian conversion,numeric formatting or status handling. Parallel0x5A06A0 writes same32-bit width; signedness does not alter emitted bits. Return incidental lower helper result.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Corrected saved STDCALL signature to THISCALL:ECX stream receiver,one32-bit stack value,RET4. Passes stack argument address/count4 to5A0990,host-order pattern without numeric conversion. Prior verified behavior retained;signature now preserves stream in array-writer pseudocode. EAX incidental lower result,array wrapper queries status separately.
int __thiscall rf_binary_stream_write_int32_host_order(void *this, int Buffer)
{
  return (int)rf_vfile_write_bytes_with_optional_feedback(this, &Buffer, 4u);
}

