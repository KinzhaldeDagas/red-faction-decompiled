// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00614BE7 _memcpy_s
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Here invalid(E) means storing errno E, calling
// invalid_parameter(NULL,NULL,NULL,0,0), and returning the stated status only if that handler returns. Cdecl(destination, unsigned capacity, source, unsigned count), returns0/22/34.
// Count0 returns0 before all pointer/capacity validation. Nonzero count with NULL destination invalid(22), no clearing. NonNULL source with capacity>=count delegates
// memcpy(destination,source,count), ignores pointer result, returns0. Otherwise memset ENTIRE declared destination capacity to zero BEFORE classifying error. NULL source takes
// precedence and invalid(22), even when capacity<count; nonNULL source with too-small capacity invalid(34). Native post-clear rechecks slots and has defensive return22 without
// errno/handler if neither condition remains, although stable ordinary arguments cannot reach it. No overlap test or independent capacity discovery; accepts capacity0 when count0,
// and may clear more bytes than requested count on error.
errno_t __cdecl memcpy_s(
        void *const Destination,
        const rsize_t DestinationSize,
        const void *const Source,
        const rsize_t SourceSize)
{
  errno_t v5; // esi

  if ( !SourceSize )
    return 0;
  if ( !Destination )
    goto LABEL_4;
  if ( Source && DestinationSize >= SourceSize )
  {
    memcpy(Destination, Source, SourceSize);
    return 0;
  }
  memset(Destination, 0, DestinationSize);
  if ( !Source )
  {
LABEL_4:
    v5 = 22;
    *_errno() = 22;
LABEL_5:
    _invalid_parameter(nullptr, nullptr, nullptr, 0, 0);
    return v5;
  }
  if ( DestinationSize < SourceSize )
  {
    *_errno() = 34;
    v5 = 34;
    goto LABEL_5;
  }
  return 22;
}

