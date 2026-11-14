// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0047A190 rf_rfl_light_destroy_name
// UNREALRED VERIFIED [level-lifecycle-20261028]: Destroys RF string at light record+4 through0x55F6D0. No other field cleanup or allocation free.
void __thiscall rf_rfl_light_destroy_name(int this)
{
  rf_string_destroy_buffer((void *)(this + 4));
}

