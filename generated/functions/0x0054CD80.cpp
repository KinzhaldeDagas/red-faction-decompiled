// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0054CD80 rf_lightmap_set_generation_preset
// UNREALRED VERIFIED (2026-11-11; original PE bytes, fresh disassembly, solid/room construction,primitive topology and centering,lightmap wire/preset/marking paths,shared ownership helpers,original ECX/stack ABI and PE bytes): Cdecl lowBYTE mode,lowBYTE variant;returns zero-extended mode. ALL paths set packed-atlas BYTE663D48=1,DWORD15A6B20=3(last pages searched),B24=128(page size),B28=65536(group allocation limit),floatB2C=0.9990000128746033(normal grouping threshold). mode!=0 also clears BYTE663CA4,sets BYTES B34=1,B35=0,B36=1,B37=1,DWORD B38=64,BYTE B3C=0. variant!=0 then DWORD B40=65535(group-size cap),B30=0;variant0 B40=65536,B30=1. mode0 ignores variant,does NOT clear663CA4,sets BYTES B34/B35/B36/B37=0,DWORD B38=0,BYTE B3C=1,DWORD B40=1,B30=1. B-prefixed offsets are full addresses15A6Bxx. No resource allocation,atlas reset,face traversal or validation. Meanings for page/group fields
// confirmed by existing atlas allocator552480 and face-cluster builder537980;remaining flags recorded by exact stores without invented units.
int __cdecl rf_lightmap_set_generation_preset(unsigned __int8 a1, char a2)
{
  int result; // eax

  result = a1;
  if ( a1 )
  {
    byte_663CA4 = 0;
    byte_663D48 = 1;
    unk_15A6B20 = 3;
    unk_15A6B34 = 1;
    unk_15A6B38 = 64;
    unk_15A6B35 = 0;
    unk_15A6B36 = 1;
    unk_15A6B37 = 1;
    if ( a2 )
    {
      unk_15A6B40 = 0xFFFF;
      unk_15A6B24 = 128;
      unk_15A6B28 = 0x10000;
      unk_15A6B2C = 0.99900001;
      unk_15A6B30 = 0;
    }
    else
    {
      unk_15A6B40 = 0x10000;
      unk_15A6B24 = 128;
      unk_15A6B28 = 0x10000;
      unk_15A6B2C = 0.99900001;
      unk_15A6B30 = 1;
    }
    unk_15A6B3C = 0;
  }
  else
  {
    byte_663D48 = 1;
    unk_15A6B20 = 3;
    unk_15A6B34 = 0;
    unk_15A6B38 = 0;
    unk_15A6B35 = 0;
    unk_15A6B36 = 0;
    unk_15A6B37 = 0;
    unk_15A6B40 = 1;
    unk_15A6B24 = 128;
    unk_15A6B28 = 0x10000;
    unk_15A6B2C = 0.99900001;
    unk_15A6B30 = 1;
    unk_15A6B3C = 1;
  }
  return result;
}

