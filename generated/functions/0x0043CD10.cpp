// IDA pseudocode evidence; not yet portable or build-ready.
// 0x0043CD10 sub_43CD10
// UNREALRED VERIFIED [combat-named-sphere-capacity-20261112]: Built modelclass sphere append40bytes atthis+4+40*count through43CD80; exactlycount8 returns-1 without writes/increment.42F6C0 ignores return, so hit-region loops useatmost8cachedsphere records evenwhenmodelqueryreportsmore.43CD60 unchecked ordinal>=8 isoutsidefixedclassarray; host must label such namedoverridebinding unsupported instead ofinventing safe native behavior.
int __thiscall sub_43CD10(
        float *this,
        float a2,
        int a3,
        int a4,
        int a5,
        int a6,
        int a7,
        int a8,
        int a9,
        int a10,
        int a11)
{
  int v12; // [esp+4h] [ebp-4h]

  if ( *(_DWORD *)this == 8 )
    return -1;
  v12 = (*(_DWORD *)this)++;
  sub_43CD80(this + 10 * v12 + 1, &a2);
  return v12;
}

