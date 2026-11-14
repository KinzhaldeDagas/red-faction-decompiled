// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0610 rf_binary_stream_write_int16_host_order
// UNREALRED VERIFIED [binary-fields-20261029]: Thiscall stream,16-bit stack value. Passes address of argument and count2 to0x5A0990; writes low16 bits in native little-endian order,without swapping. Parallel unsigned WORD writer0x5A0640 has equivalent raw-width behavior. Return is lower helper incidental result.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Corrected saved STDCALL signature to THISCALL:ECX stream receiver plus one16-bit stack value. Body passes address of stack value,count2 to5A0990 optional-feedback writer;RET4. Writes native low16 pattern,no byte swap. Existing behavior comment preserved. Return is lower helper incidental EAX,not reliable pointer/count/status;array writer separately queries stream status. Source caller array not passed by address.
int __thiscall rf_binary_stream_write_int16_host_order(void *this, __int16 Buffer)
{
  return (int)rf_vfile_write_bytes_with_optional_feedback(this, &Buffer, 2u);
}

