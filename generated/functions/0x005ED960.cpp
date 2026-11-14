// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED960 rf_acm_shutdown_driver_if_ready
// UNREALRED VERIFIED [wave-codec-20261028]: If ready byte0x1F6710C nonzero,calls acmDriverClose(global0x1F67100,0),clears ready regardless result. Does not null driver handle/ID or free stored DLL handle. If ready0,returns0 without touching a possibly leaked driver from failed initialization. Returns driver close result or prior ready0.
MMRESULT rf_acm_shutdown_driver_if_ready()
{
  MMRESULT result; // eax

  result = byte_1F6710C[0];
  if ( byte_1F6710C[0] )
  {
    result = acmDriverClose(*(HACMDRIVER *)&byte_1F670FC[4], 0);
    byte_1F6710C[0] = 0;
  }
  return result;
}

