// IDA pseudocode evidence; not yet portable or build-ready.
// 0x005ED880 rf_acm_initialize_ms_adpcm_driver
// UNREALRED VERIFIED [wave-codec-20261028]: If ready byte0x1F6710C==1,returns0. LoadLibrary(msacm32.dll) into global0x1F67104; failure-1. Immediately FreeLibrary on success,leaving stored handle stale. Requires signed acmGetVersion>=53608448,enumerates flags0x80000000 through0x5ED580,requires selected driver ID,opens driver to0x1F67100 and calls acmDriverPriority(id,0,0). Any error-1. Priority failure leaves opened driver handle while ready remains0; normal shutdown gates on ready and will skip it. Success ready1,return0. No reset of prior selected ID or rollback of partially initialized globals.
int rf_acm_initialize_ms_adpcm_driver()
{
  if ( byte_1F6710C[0] == 1 )
    return 0;
  *(_DWORD *)&byte_1F670FC[8] = LoadLibraryA("msacm32.dll");
  if ( !*(_DWORD *)&byte_1F670FC[8] )
    return -1;
  FreeLibrary(*(HMODULE *)&byte_1F670FC[8]);
  if ( (int)acmGetVersion() < 53608448 )
    return -1;
  if ( acmDriverEnum((ACMDRIVERENUMCB)rf_acm_enumerate_ms_adpcm_driver_callback, 0, 0x80000000) )
    return -1;
  if ( !*(_DWORD *)&byte_1F670FC[12] )
    return -1;
  if ( acmDriverOpen((LPHACMDRIVER)&byte_1F670FC[4], *(HACMDRIVERID *)&byte_1F670FC[12], 0) )
    return -1;
  if ( acmDriverPriority(*(HACMDRIVERID *)&byte_1F670FC[12], 0, 0) )
    return -1;
  byte_1F6710C[0] = 1;
  return 0;
}

