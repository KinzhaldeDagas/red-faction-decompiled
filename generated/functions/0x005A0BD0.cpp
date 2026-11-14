// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005A0BD0 rf_binary_stream_serialize_bool
// UNREALRED VERIFIED [mission-startup-20261020] Versioned BOOLEAN read-into wrapper. Delegates to0x59F840; successful version180 bytes2 and255 become1 before loader compares with1. Do not interpret raw bool storage using raw==1.
// UNREALRED VERIFIED [stream-serializers-20261029]: Arguments value BYTE pointer,minimum version,fallback BYTE. READ stores0x59F840 result,which normalizes successfully read nonzero bytes to1. WRITE delegates0x5A0590,which writes1 ONLY for input BYTE==1,else0. Prior read-only name omitted write branch; existing mission-startup comment remains valid for read path. Thiscall stream in ECX. Tests slot mode bit1 through0x592440: set selects READ,clear selects WRITE. Minimum version and fallback apply only on read; write does not version-gate. Return is branch-dependent helper/value,not a common success code. No pointer validation or rollback.
unsigned __int8 __thiscall rf_binary_stream_serialize_bool(int *this, char *a2, int a3, char a4)
{
  unsigned __int8 result; // al

  if ( !rf_vfile_test_mode_mask(this, 1) )
    return (unsigned __int8)rf_binary_stream_write_bool_equal_one(this, *a2);
  result = rf_binary_stream_read_bool_versioned(this, a3, a4);
  *a2 = result;
  return result;
}

