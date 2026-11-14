// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0C70 rf_binary_stream_serialize_uint8
// UNREALRED VERIFIED [mission-startup-20261020] Versioned RAW-byte read-into wrapper. Delegates to0x59F900, stores its single byte without boolean normalization. RFL trigger NPC policy uses this wrapper; values2,3,4,5 must survive.
// UNREALRED VERIFIED [stream-serializers-20261029]: Arguments BYTE pointer,minimum version,fallback BYTE. READ stores0x59F900 raw byte without boolean normalization. WRITE sends byte through0x5A05F0. Values2..255 survive either raw path. Prior read-only name omitted write branch. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
char __thiscall rf_binary_stream_serialize_uint8(int *this, char *a2, int a3, char a4)
{
  char result; // al

  if ( !rf_vfile_test_mode_mask(this, 1) )
    return (unsigned __int8)rf_binary_stream_write_byte_host_order(this, *a2);
  result = rf_binary_stream_read_byte_versioned(this, a3, a4);
  *a2 = result;
  return result;
}

