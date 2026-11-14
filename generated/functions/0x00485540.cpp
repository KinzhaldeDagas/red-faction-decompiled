// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00485540 rf_geomod_snapshot_record_construct
// UNREALRED VERIFIED [level-state-file-cache-flow-20261028] Call raw short-quaternion constructor at32-byte GeoMod record+20 then return. No quantized position, radius/material/event fields or full-record zeroing in this constructor.
char *__thiscall rf_geomod_snapshot_record_construct(char *this)
{
  rf_short_quaternion_construct_0001((_WORD *)this + 10);
  return this;
}

