// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00500FB0 rf_event_skybox_state_apply_forward
// UNREALRED VERIFIED [authored-sky-renderer] Copies the authored axis byte at +0x2B8 and angular speed at +0x2BC into the global skybox state. It does not reset the accumulated angle and does not control sky visibility.
int __thiscall rf_event_skybox_state_apply_forward(int this)
{
  rf_skybox_rotation_axis = *(_BYTE *)(this + 696);
  rf_skybox_rotation_degrees_per_second = *(float *)(this + 700);
  return this;
}

