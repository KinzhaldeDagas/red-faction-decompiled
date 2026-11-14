// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00515610 rf_benchmark_write_timedemo_log
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, timedemo/framerate state machine,x87FPS extrema,log ABI and recovered console handlers,original ECX/stack flow and PE bytes): CdecltextCString,caller pops4. Construct localVFile;calltime64 wrapper5157A0 into64-bit local thenlocaltime64 wrapper515780,even when timestampwillnotbeused. If navModeBYTE92DE10 nonzero AND signednavIndex92DDF8 !=0,formattext alone with%s;otherwise format asctime(tm)+text using%s%s. No bounds,formatting-return,clock/localtimeNULL or textNULL checks. Open timedemo.txt through5930A0 with modeDWORD0x80000002 and NUMERIC context9999999(0x98967F);IDA offsetunk_98967F display is NOT a pointer dereference. Ignore open result. Scan formattedNULtext for exact strlen(excluding terminator),pass length andbuffer to5A0AB0 directstdio-line helper. That helper writes suppliedbytes thenoneLF on
// success,retaining any existing asctime/message newlines andbypassingVFile feedback/counters. Closeexplicitly then destruct localVFile;returns destructorEAXresidue,not write-success. No benchmarkstatistic mutation or retry.
int __cdecl rf_benchmark_write_timedemo_log(const char *a1)
{
  char *v1; // eax
  char Buffer; // [esp+14h] [ebp-23Ch] BYREF
  _BYTE v4[3]; // [esp+15h] [ebp-23Bh] BYREF
  struct tm *Tm; // [esp+118h] [ebp-138h]
  int self[71]; // [esp+11Ch] [ebp-134h] BYREF
  __time64_t Time; // [esp+23Ch] [ebp-14h] BYREF
  int v8; // [esp+24Ch] [ebp-4h]

  rf_vfile_construct_unopened(self);
  v8 = 0;
  rf_benchmark_time64_forward(&Time);
  Tm = rf_benchmark_localtime64_forward(&Time);
  if ( byte_92DE10 && dword_92DDF8 )
  {
    sprintf(&Buffer, "%s", a1);
  }
  else
  {
    v1 = asctime(Tm);
    sprintf(&Buffer, "%s%s", v1, a1);
  }
  rf_vfile_open_with_extension_cache_control_paths(self, "timedemo.txt", -2147483646, byte_98967F);
  rf_vfile_write_line_stdio_direct(self, &Buffer, &v4[strlen(&Buffer)] - v4);
  rf_vfile_close_stdio_or_vpp(self);
  v8 = -1;
  return rf_vfile_destruct_close_if_open(self);
}

