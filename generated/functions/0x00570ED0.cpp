// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00570ED0 rf_renderer_read_sst_dualhead_environment_for_mode201
// UNREALRED VERIFIED (2026-11-04; original PE bytes, fresh disassembly, renderer/window context, capture ownership across calls, gamma precision and ramp bytes): No args. Only when context windowMode187CCA0==201,queries SST_DUALHEAD into32B local with API capacity31,sets context DWORD187CCA4=0,and if returned length nonzero stores atoi(buffer)!=0. No check that returned length fits capacity or explicit terminator write;any nonzero value,including negative numeric text,enables. Other window modes leave field untouched. Generic initializer zeroes context before calling this.
void rf_renderer_read_sst_dualhead_environment_for_mode201()
{
  DWORD EnvironmentVariableA; // [esp+4h] [ebp-28h]
  CHAR Buffer[32]; // [esp+8h] [ebp-24h] BYREF

  if ( unk_187CCA0 == 201 )
  {
    EnvironmentVariableA = GetEnvironmentVariableA("SST_DUALHEAD", Buffer, 0x1Fu);
    unk_187CCA4 = 0;
    if ( EnvironmentVariableA )
      unk_187CCA4 = atoi(Buffer) != 0;
  }
}

