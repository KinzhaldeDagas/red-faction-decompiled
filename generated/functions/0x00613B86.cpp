// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00613B86 ___tzset
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review): Noargs void lazy timezone initialization. Read
// initializedDWORD2021C64 outside lock; nonzero returns immediately. Otherwise acquire lock6,arm EH4scope65ED60,RECHECKflag; stillzero calltzset_nolock (which takeslock7 internally),
// incrementflagONLYafter normalreturn. Finallyunlock6 normal/unwind via613BCC. If initializer returns despite OS/allocationfailure,flag stillbecomes1 and futurecalls skip. No forced
// refresh, per-thread initialization, memorybarrier beyond lock implementation or outputstatus.
void __tzset()
{
  if ( !unk_2021C64 )
  {
    _lock(6);
    if ( !unk_2021C64 )
    {
      _tzset_nolock();
      ++unk_2021C64;
    }
    _unlock(6);
  }
}

