// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00600300 rf_jpeg_mem_term
// UNREALRED VERIFIED (2026-10-29; original PE bytes and fresh disassembly; IJG v6b jmemnobs.c:jpeg_mem_term matched): Cdecl(cinfo),bodyisno-opret;unusedargumentverifiedself_destructpushes cinfoandcleans4. Doesnotfreepools,FILEsorglobaltables;poolcleanupoccursincaller. Oldinferredvoid(void)omittedABIargument;APIvoid.
void __cdecl rf_jpeg_mem_term(void *cinfo)
{
  ;
}

