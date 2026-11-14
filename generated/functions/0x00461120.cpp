// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00461120 rf_browser_release_record_and_index_arrays
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh disassembly, menu/profile call chains, endpoint/index sorting, native allocation/float/callback ABI and original
// switch/registry data): Noarg. Entire cleanup gated ONLY on primary6F52CC nonNULL. Delete primary,zero it;delete index array6F52D4,zero it;delete6F52D0,zero it;then clear live
// recordCount6F51A8,visibleCount6F5088 and capacity6F5198. If primaryNULL,even other nonNULL secondary pointers/counts left untouched. No per-record destructor,string release
// (records are inline bytes),selection661F9C/query timer reset or array object ownership. Existing void prototype retained.
void rf_browser_release_record_and_index_arrays()
{
  if ( dword_6F52CC )
  {
    operator delete(dword_6F52CC);
    dword_6F52CC = nullptr;
    operator delete(MEMORY[0x6F52D4]);
    MEMORY[0x6F52D4] = nullptr;
    operator delete(unk_6F52D0);
    unk_6F52D0 = 0;
    unk_6F51A8 = 0;
    MEMORY[0x6F5088] = 0;
    unk_6F5198 = 0;
  }
}

