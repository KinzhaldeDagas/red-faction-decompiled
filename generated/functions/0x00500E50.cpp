// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500E50 rf_event_set_gravity_forward
// UNREALRED VERIFIED [mission-goal-timer-threshold-continuation-20261027] event_set_gravity forward, vtable0x63E280 slot+4. Pass raw float event+0x2B8 to gravity setter0x4DA120. No target iteration, unit conversion, clamp or per-event saved previous gravity in this body; reverse uses generic reverse handler.
float *__thiscall rf_event_set_gravity_forward(float *this)
{
  return rf_physics_set_gravity_acceleration(*(this + 174));
}

