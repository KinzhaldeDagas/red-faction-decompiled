// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0061A5E0 ___dtoxmode
// UNREALRED VERIFIED (2026-11-12; original PE bytes, fresh native disassembly/decompilation, native control-flow and ABI review):
// Cdecl(attributeLOWBYTE,filename),unsignedmodeEAX;noNULLguard. Readfilename[1]withoutlengthcheck;ifcolon,classificationcursor=filename+2,elseoriginal.
// Base4040h(directory+ownerexecute)ifcursorisSOLEslash/backslash,attributesbit10hset,ORcursorNUL;elsebase8000h(regular).
// Alwaysownerread100h;ownerwrite80hiffattributeREADONLYbit0clear. FindLASTdotvia mbsrchr onORIGINALentirefilename;case-insensitiveFULLsuffixmatches .exe/.cmd/.bat/.com via mbsicmp
// ->ORownerexecute40h,notjustextensionprefix. Directory/pathseparatorsnotseparatelyexcludedfromsuffixscan. ReplicateownerRWXto group=(mode>>3)&38h
// thenother=(intermediate>>6)&7,returncombined. No filesystemquery,rangevalidation,allocation,ownerrnoorlocaleobject; delegatedsearch/collationusescurrentlocale.
unsigned int __cdecl __dtoxmode(char a1, unsigned __int8 *String)
{
  unsigned __int8 *v2; // ecx
  unsigned __int8 v3; // dl
  int v4; // edi
  unsigned int v5; // edi
  unsigned __int8 *v6; // eax
  const unsigned __int8 *v7; // esi

  v2 = String;
  if ( String[1] == 58 )
    v2 = String + 2;
  v3 = *v2;
  if ( (*v2 == 92 || v3 == 47) && !v2[1] || (a1 & 0x10) != 0 || (v4 = 0x8000, !v3) )
    v4 = 16448;
  v5 = ~(a1 << 7) & 0x80 | 0x100 | v4;
  v6 = _mbsrchr(String, 0x2Eu);
  v7 = v6;
  if ( v6 && (!_mbsicmp(v6, ".exe") || !_mbsicmp(v7, ".cmd") || !_mbsicmp(v7, ".bat") || !_mbsicmp(v7, ".com")) )
    v5 |= 0x40u;
  return (v5 >> 3) & 0x38 | v5 | (((v5 >> 3) & 0x38 | v5) >> 6) & 7;
}

