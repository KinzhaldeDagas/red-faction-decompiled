// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED3B0 rf_dsound3d_shutdown_if_ready
// UNREALRED VERIFIED [wave-codec-20261028]: If ready byte0x1F670FC nonzero,calls0x5ED3D0 then clears ready. Does not release emitter3D interfaces,device or property interface. Ready0 returns0 without releasing a listener obtained separately; otherwise returns release helper result.
int rf_dsound3d_shutdown_if_ready()
{
  int result; // eax

  result = byte_1F670FC[0];
  if ( byte_1F670FC[0] )
  {
    result = rf_dsound3d_release_listener_interface();
    byte_1F670FC[0] = 0;
  }
  return result;
}

