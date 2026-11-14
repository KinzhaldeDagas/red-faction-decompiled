// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0700 rf_binary_stream_write_vector3
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall stream,mutable3-float source pointer. Forwards0x5A0990(stream,source,12). Does not byte-swap,convert floats,normalize vector or inspect write status. Source may be temporarily modified by lower writer when feedback encoding enabled. Return is lower writer incidental result,not guaranteed pointer or byte count.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Corrected saved STDCALL signature to THISCALL ECX stream plus mutable source3f pointer,RET4. Forwards source/count12 to5A0990 optional-feedback writer. No normalization,swap or status query. Lower helper can temporarily modify source during feedback encoding;source therefore kept mutable. Return incidental lower EAX;existing vector-array writer queries stream status after each call.
int __thiscall rf_binary_stream_write_vector3(void *this, float *Buffer)
{
  return (int)rf_vfile_write_bytes_with_optional_feedback(this, Buffer, 0xCu);
}

