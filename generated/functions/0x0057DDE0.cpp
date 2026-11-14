// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0057DDE0 rf_stream_adapter_read_u16_string_to_buffer
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, character bone hierarchy, adapter branches, action/trigger callers and PE-verified affine constants): Mode0 forwards all arguments to virtual-stream u16-string reader. Memory mode maps capacity-1 to65535. If version sufficient: reads unsigned16 payload length; zero clears destination[0]. If length>=capacity, bulk-reads capacity-1, appendsNUL and discards remaining bytes via char reader; otherwise bulk-reads length and terminates there. Bulk exact-end failure is NOT checked, so output payload can remain stale while terminator is written. Older version strncpy-copies default without guaranteeing termination, or writes empty for NULL default. No guard for zero/negative capacity or invalid destination. AX return is branch-dependent, not a reliable byte count.
__int16 __thiscall rf_stream_adapter_read_u16_string_to_buffer(
        _DWORD *this,
        char *Destination,
        int Count,
        int a4,
        char *Source)
{
  __int16 result; // ax
  unsigned __int16 uint16; // ax
  signed int i; // [esp+4h] [ebp-8h]
  size_t Size; // [esp+8h] [ebp-4h]

  if ( !*this )
    return rf_binary_stream_read_u16_string_to_buffer((int *)*(this + 1), Destination, Count, a4, Source);
  if ( Count == -1 )
    Count = 0xFFFF;
  if ( *(this + 20) >= a4 )
  {
    uint16 = rf_stream_adapter_read_uint16(this);
    Size = uint16;
    if ( uint16 )
    {
      if ( uint16 >= Count )
      {
        result = rf_stream_adapter_read_bytes((int **)this, Destination, Count - 1);
        Destination[Count - 1] = 0;
        for ( i = 0; i < (int)(Size - (Count - 1)); ++i )
        {
          rf_stream_adapter_read_char8(this);
          result = i + 1;
        }
      }
      else
      {
        result = rf_stream_adapter_read_bytes((int **)this, Destination, uint16);
        Destination[Size] = 0;
      }
    }
    else
    {
      *Destination = 0;
      return (__int16)Destination;
    }
  }
  else if ( Source )
  {
    return (unsigned __int16)strncpy(Destination, Source, Count);
  }
  else
  {
    *Destination = 0;
    return (__int16)Destination;
  }
  return result;
}

