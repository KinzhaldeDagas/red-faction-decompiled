// IDA pseudocode evidence; not yet portable or build-ready.
// 0x004A6AF0 rf_net_statistics_accept_latency_response
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, replication transport admission/flush policy, item packet40/43/45 codecs, identifier mapping, traffic histories and latency timing): 
// Thiscall(stats), no runtime/authority guard. If outstanding performance-clock stamp DWORD+1420 is signed>=0, computes raw wrapping signed milliseconds
// now(performance_clock_scaled1000)-stamp. With signed sample count+1412<2, writes sample at stats+1404+count*4 and increments count (no negative-count guard); otherwise memcpy4
// bytes from second sample+1408 to first+1404 and writes new second sample without increasing count. No elapsed sign/wrap normalization or averaging here.
// Always sets outstanding stamp+1420=-1 and arms wrapped game-clock retry deadline+1416 for1200ms, including unsolicited response with no outstanding stamp. Returns deadline delegate
// result; does not send packet or alter byte histories. Current incoming xref lies in unclassified code; successful live reply dispatch is not established solely here.
int __thiscall rf_net_statistics_accept_latency_response(int *this)
{
  int v3; // [esp+4h] [ebp-4h]

  if ( *(this + 355) >= 0 )
  {
    v3 = rf_performance_clock_elapsed_scaled(1000) - *(this + 355);
    if ( *(this + 353) < 2 )
    {
      *(this + (*(this + 353))++ + 351) = v3;
    }
    else
    {
      memcpy_0(this + 351, this + 352, sizeof(int));
      *(this + 352) = v3;
    }
  }
  *(this + 355) = -1;
  return rf_clock_deadline_set_wrapped_offset(this + 354, 1200);
}

