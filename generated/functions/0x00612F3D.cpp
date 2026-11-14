// IDA pseudocode evidence; not yet portable or build-ready.
// 0x00612F3D ___initmbctable
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, caller/static-initializer ownership, complete native stack/x87/SEH paths and
// library-label review): No args. If global2022F94==0 call setmbcp(-3),IGNORE result,then set flag1. Nonzero flag skips. Always return0; failed first initialization still suppresses
// future retry. No atomic once/lock or codepage validation in wrapper; no unconditional table rebuild.
int __initmbctable()
{
  if ( !unk_2022F94 )
  {
    _setmbcp(-3);
    unk_2022F94 = 1;
  }
  return 0;
}

