// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0055F290 rf_clock_deadline_disarm
// UNREALRED VERIFIED [network-queues-20261028]: Thiscall pointer to deadline DWORD. Stores0xFFFFFFFF and returns same pointer. No clock read,allocation or elapsed calculation; used to mark wrapping deadline unarmed.
_DWORD *__thiscall rf_clock_deadline_disarm(_DWORD *this)
{
  *this = -1;
  return this;
}

