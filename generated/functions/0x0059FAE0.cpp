// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0059FAE0 rf_binary_stream_read_vector3_versioned
// UNREALRED VERIFIED [string-pool-stream-20261028]: Thiscall stream; logical stack arguments destination vector,minimum version,default vector pointer. If rf_binary_stream_version_at_least(stream,minimum),calls0x5A0230(stream,destination,12,minimum,0). Otherwise copies3 floats from default via vector helper. Stream pointer belongs in ECX; misleading caller decompilations can show destination as this. Returns path-dependent byte-read count or vector-helper pointer,NOT common0/status. Version fallback does not read stream or set error. No destination/default validation.
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, arena lifecycle and resize paths, stream receiver ABI, array serialization loops and original PE bytes): Corrected saved STDCALL ABI to THISCALL ECX stream plus destination3f,minimumVersion,default3f pointer. If version sufficient,forwards destination,12 bytes,minimum,mode0 to5A0230. Else copies default vector to destination via vector helper without reading stream. Return path-dependent byte-read result or vector-helper EAX,not common status. No NULL/default/finite guard or separate normalization;existing verified behavior comment retained.
int __thiscall rf_binary_stream_read_vector3_versioned(void *this, float *destination, int a3, const float *a4)
{
  float copy_result[3]; // [esp+4h] [ebp-Ch] BYREF

  if ( rf_binary_stream_version_at_least(this, a3) )
    return rf_vfile_read_buffered_bytes_versioned((int *)this, (char *)destination, 0xCu, a3, 0);
  else
    return (int)rf_vector_copy(destination, copy_result, a4);
}

