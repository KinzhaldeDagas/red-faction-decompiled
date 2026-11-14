// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0060F945 __sse2_mathfcns_init
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No args. First clear global2021F60=0,call get_sse2_info,then overwrite SAME global with rawEAX. Return0 viaXOR. Two stores real even if final value0; no own
// feature test, one-time flag, instruction patch or error propagation.
int _sse2_mathfcns_init()
{
  unk_2021F60 = 0;
  unk_2021F60 = _get_sse2_info();
  return 0;
}

